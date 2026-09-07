#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <move_to_point_action/action/move_to_point.hpp>

/*
Для призыва черепахи
    ros2 run turtlesim turtlesim_node
    ros2 run turtlesim turtle_teleop_key
*/

/*
Задачи
Релизовать управление черепахой для достижения заданой точки.
Для этого
Выполнить проверку достижимости полученной цели в сервере дйствия (0...11)
Релизовать алгоритм поворота и достижения в заданную точку в соответсвующей функции
Отправлять обратную связь в ходе движения и приводить её в диапазон (0...100)
Подписчик на текущие координаты черепахи и публикатор скорости geometry_msgs/Twist в топик /turtle1/cmd_vel
    Дополнить интерфейс управления след возможностями
Деактивацией кнопки запуска движения при выполении действия. После выполения действия кнопка снова становится активной
Реализовать кнопку отмены движения, которая будет вызывать функцию
/// action_clien->async_cancel_goal(current_goal_handle);
При этом черепаха должна остановиться
Написать launch файл для реализации запуска двух узлов + симуляция
*/

class MoveToPointServer: public rclcpp::Node
{
public:
    // Для удобства используем локальные сокращения
    using MoveToPoint = move_to_point_action::action::MoveToPoint;
    using GoalHandleMoveToPoint = rclcpp_action::ServerGoalHandle<MoveToPoint>;

    MoveToPointServer() : Node("move_to_point_server_node")
    {
        action_server = rclcpp_action::create_server<MoveToPoint>
            (
                this,
                "move_to_point",
                std::bind(&MoveToPointServer::handle_goal,this, std::placeholders::_1, std::placeholders::_2),
                std::bind(&MoveToPointServer::handle_cancel,this,std::placeholders::_1),
                std::bind(&MoveToPointServer::handle_accepted,this,std::placeholders::_1)
            );
        pose_sub = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&MoveToPointServer::pose_callback,this,std::placeholders::_1));
        cmd_pub = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
    }

private:
    // Объект сервера действия
    rclcpp_action::Server<MoveToPoint>::SharedPtr action_server;
    // Подписчик на текущие координаты черепахи
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub;
    // Публикатор скорости для черепахи
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub;

    float turtle_goal_x, turtle_goal_y; // Координаты цели для черепахи
    float turtle_current_x, turtle_current_y, turtle_current_theta; // Текущие координаты черепахи

    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        turtle_current_x = msg->x;
        turtle_current_y = msg->y;
        turtle_current_theta = msg->theta;
    }

    // 1. Обработчик цели
    /*
    Сюда поступает цель действия, нужно по ее параметрам понять,
    пригодно ли она для исполнения и если да, то принять ее , если нет - то отклонить
    */

    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &uuid, // Идентификатор
                                            std::shared_ptr<const MoveToPoint::Goal> goal) // Цель
    {
        // Поскольку цель --- это точка, то при ее поступлении нужно понять, достижима ли она
        RCLCPP_INFO_STREAM(this->get_logger(), "Получена целевая точка "<< goal->target_point.x<<" "<<goal->target_point.y);
        // Вставить проверку
        if ((goal->target_point.x > 0 && goal->target_point.x < 11) && (goal->target_point.y > 0 && goal->target_point.y < 11))
        {
            turtle_goal_x = goal->target_point.x;
            turtle_goal_y = goal->target_point.y;
            // Если точка устраивает
            return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
        }
        else
        {
            return rclcpp_action::GoalResponse::REJECT; // При недостижимости
        }
    }

    // 2. Обработка на отмену действия
    // Здесь выполняется запрос на прекращения выполнения операции
    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandleMoveToPoint> goal_handle)
    {
        RCLCPP_WARN_STREAM(this->get_logger(), "Запрос на отмену действия");
        // Если мы принимаем запрос, то вернуть
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
        cmd_pub->publish(msg);
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    // 3. Запуск действия
    // Если цель принята, то необходимо запустить выполнение действия
    void handle_accepted (
        const std::shared_ptr<GoalHandleMoveToPoint> goal_handle)
    {
        // В отдельном потоке запускаем исполнение действия
        std::thread{std::bind(&MoveToPointServer::execute,this,std::placeholders::_1), goal_handle}.detach();
    }

    // 4. Исполнительная функция, которая реализует действие и работает в отдельном потоке
    void execute (
        const std::shared_ptr<GoalHandleMoveToPoint> goal_handle)
    {
        // Здесь реализуется алгоритм достижения цели
        RCLCPP_INFO_STREAM(this->get_logger(),"Начало движения к цели");
        rclcpp::Rate loop_rate(10);

        // Параметр цели
        auto goal = goal_handle->get_goal();

        // Обратная связь
        auto feedback = std::make_shared<MoveToPoint::Feedback>();

        // Итоговый результат
        auto result = std::make_shared<MoveToPoint::Result>();

        // Коэффициенты PID регулятора для линейной скорости
        float Kp_linear = 0.8;   // Пропорциональный коэффициент для линейной скорости
        float Ki_linear = 0.07;   // Интегральный коэффициент для линейной скорости
        float Kd_linear = 0.1;    // Дифференциальный коэффициент для линейной скорости

        // Коэффициенты PID регулятора для угловой скорости
        float Kp_angular = 2.6;   // Пропорциональный коэффициент для угловой скорости
        float Ki_angular = 0;    // Интегральный коэффициент для угловой скорости
        float Kd_angular = 0;    // Дифференциальный коэффициент для угловой скорости

        // Переменные для PID регуляторов
        float integral_linear = 0.0;
        float prev_error_linear = 0.0;
        float integral_angular = 0.0;
        float prev_error_angular = 0.0;

        // Пороговые значения
        float distance_threshold = 0.001;      // Порог расстояния для остановки
        float angle_threshold = 0.005;         // Порог угла для поворота
        float max_linear_speed = 1.5;         // Максимальная линейная скорость
        float max_angular_speed = 1.0;        // Максимальная угловая скорость

        // Время для dt
        auto last_time = this->now();

        // Основной цикл действия
        float distance = sqrt(pow(turtle_goal_x - turtle_current_x, 2) +
                              pow(turtle_goal_y - turtle_current_y, 2));
        float start_distance = distance;
        geometry_msgs::msg::Twist msg;

        while ((distance > distance_threshold) && (rclcpp::ok()))
        {
            // Вычисляем dt
            auto current_time = this->now();
            float dt = (current_time - last_time).seconds();
            last_time = current_time;

            // Проверяем, не отменена ли цель
            if (goal_handle->is_canceling())
            {
                // Останавливаем движение
                msg.linear.x = 0.0;
                msg.angular.z = 0.0;
                cmd_pub->publish(msg);

                // Формируем результат
                result->success = false;
                goal_handle->canceled(result);
                RCLCPP_INFO_STREAM(this->get_logger(), "Цель отменена");
                return;
            }

            // Обновляем текущую позицию (предполагается, что она обновляется в другом месте)
            distance = sqrt(pow(turtle_goal_x - turtle_current_x, 2) +
                            pow(turtle_goal_y - turtle_current_y, 2));

            // Вычисляем желаемый угол к цели
            float turtle_goal_theta = atan2((turtle_goal_y - turtle_current_y),
                                            (turtle_goal_x - turtle_current_x));

            // Вычисляем ошибку по углу
            float angle_error = turtle_goal_theta - turtle_current_theta;

            // Нормализуем угол в диапазон [-PI, PI]
            while (angle_error > M_PI) angle_error -= 2.0 * M_PI;
            while (angle_error < -M_PI) angle_error += 2.0 * M_PI;

            // --- PID регулятор для угловой скорости ---
            // Пропорциональная составляющая
            float angular_p = Kp_angular * angle_error;

            // Интегральная составляющая (с ограничением для предотвращения накопления)
            integral_angular += angle_error * dt;
            // Ограничиваем интеграл для предотвращения переполнения
            integral_angular = std::max(-1.0f, std::min(1.0f, integral_angular));
            float angular_i = Ki_angular * integral_angular;

            // Дифференциальная составляющая
            float angular_d = 0.0;
            if (dt > 0) {
                angular_d = Kd_angular * ((angle_error - prev_error_angular) / dt);
            }

            // Суммируем составляющие
            float angular_correction = angular_p + angular_i + angular_d;

            // Ограничиваем угловую скорость
            msg.angular.z = std::max(-max_angular_speed,
                                     std::min(max_angular_speed, angular_correction));

            // Сохраняем ошибку для следующей итерации
            prev_error_angular = angle_error;

            // --- PID регулятор для линейной скорости ---
            // Применяем линейную скорость только если угол достаточно мал
            if (fabs(angle_error) < angle_threshold) {
                // Ошибка по расстоянию
                float distance_error = distance;

                // Пропорциональная составляющая
                float linear_p = Kp_linear * distance_error;

                // Интегральная составляющая
                integral_linear += distance_error * dt;
                integral_linear = std::max(-1.0f, std::min(1.0f, integral_linear));
                float linear_i = Ki_linear * integral_linear;

                // Дифференциальная составляющая
                float linear_d = 0.0;
                if (dt > 0) {
                    linear_d = Kd_linear * ((distance_error - prev_error_linear) / dt);
                }

                // Суммируем составляющие
                float linear_correction = linear_p + linear_i + linear_d;

                // Ограничиваем линейную скорость
                msg.linear.x = std::max(0.0f, std::min(max_linear_speed, linear_correction));

                // Сохраняем ошибку для следующей итерации
                prev_error_linear = distance_error;
            } else {
                // Если угол слишком большой, не едем вперед
                msg.linear.x = 0.0;
                // Сбрасываем интегральную составляющую линейной скорости
                integral_linear = 0.0;
                prev_error_linear = 0.0;
            }

            // Публикуем команду скорости
            cmd_pub->publish(msg);

            // Формируем обратную связь
            feedback->progress = (1.0 - distance / start_distance) * 100;
            goal_handle->publish_feedback(feedback);

            // Логирование для отладки
            RCLCPP_DEBUG_STREAM(get_logger(),
                                "Расстояние: " << distance <<
                                    ", Угол: " << angle_error <<
                                    ", Лин. скорость: " << msg.linear.x <<
                                    ", Угл. скорость: " << msg.angular.z);

            loop_rate.sleep(); // Засыпаем для поддержания желаемой частоты
        }

        // После окончания выполнения действия необходимо отправить результат
        if (rclcpp::ok())
        {
            // Полная остановка
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
            cmd_pub->publish(msg);

            result->success = true;
            goal_handle->succeed(result);
            RCLCPP_INFO_STREAM(this->get_logger(), "Цель достигнута");
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MoveToPointServer>());
    rclcpp::shutdown();
    return 0;
}
