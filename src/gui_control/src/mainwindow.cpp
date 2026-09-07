#include <mainwindow.h>
#include "ui_mainwindow.h"



MainWindow::MainWindow(rclcpp::Node::SharedPtr n, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    node(n),
    current_state_fsm(waiting),
    current_state_petri{true, false, false, false},
    path_ready{false}
{
    ui->setupUi(this);
    // Подписчик на позицию черепахи
    pose_sub = node->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&MainWindow::pose_callback,this,std::placeholders::_1));
    action_client = rclcpp_action::create_client<MoveToPoint>(node, "move_to_point");
    // Клиент сервиса для сброса черепахи
    reset_srv = node->create_client<std_srvs::srv::Empty>("/reset");

    this->do_thing();
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
{
    QString label_text = "X: " + QString::number(msg->x) + "  Y: " + QString::number(msg->y) + "  Theta: " + QString::number(msg->theta);
    ui -> label_pose->setText(label_text);
}



void MainWindow::on_pushButton_reset_clicked()
{
    (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("reset") : this->processEvent_petri("reset");
    X_points.clear();
    Y_points.clear();
    on_point = 0;
    ui->textEdit_log->clear();
    send_cancel();

    path_ready = false;
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    reset_srv->async_send_request(request);
}



void MainWindow::goal_responce_callback(const GoalHandleMoveToPoint::SharedPtr &goal_handle)
{
    //  Проверяем принята ли цель
    if(!goal_handle)
    {
        QMetaObject::invokeMethod(this, [this]()
                                  {
            // Если цель не принята
            ui->lineEdit_status->setText("Цель отклонена");
            // this->processEvent_fsm("error");
            (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("error") : this->processEvent_petri("error");
            ui->pushButton_sendToGoal->setEnabled(true);
        });

    }
    else
    {
        QMetaObject::invokeMethod(this, [this]()
                                  {
                    ui->lineEdit_status->setText("Сервер принял цель, начало движения...");
                    ui->pushButton_sendToGoal->setEnabled(false);
        });

    }
}



void MainWindow::feedback_callback(GoalHandleMoveToPoint::SharedPtr, const std::shared_ptr<const MoveToPoint::Feedback> feedback)
{
    // Функция обрабатывает обратную связь от процесса
    QMetaObject::invokeMethod(this, [this, feedback](){
        ui->progressBar_goal->setValue(feedback->progress);
    });
}



void MainWindow::result_callback(const GoalHandleMoveToPoint::WrappedResult &result)
{
    QMetaObject::invokeMethod(this, [this, result]()
                              {
        switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            if(current_state_fsm == executing_path || current_state_petri.executing_path)
                this->execut_path();
            else
                // this->processEvent_fsm("succeeded");
                (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("succeeded") : this->processEvent_petri("succeeded");
            break;
        case rclcpp_action::ResultCode::ABORTED:
            // this->processEvent_fsm("error");
            (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("error") : this->processEvent_petri("error");
            break;
        case rclcpp_action::ResultCode::CANCELED:
            if(current_state_fsm == executing_path || current_state_petri.executing_path)
                this->execut_path();
            else
                // this->processEvent_fsm("cancel");
                (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("cancel") : this->processEvent_petri("cancel");
            break;
        default:
            // this->processEvent_fsm("error");
            (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("error") : this->processEvent_petri("error");
            return;
        }
        ui->pushButton_sendToGoal->setEnabled(true);
    }
                              );

}



void MainWindow::on_pushButton_sendToGoal_clicked()
{
    // processEvent_fsm("execute_point");
    (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("execute_point") : this->processEvent_petri("execute_point");
}



void MainWindow::on_pushButton_startMisson_clicked()
{
    // processEvent_fsm("execute_path");
    (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("execute_path") : this->processEvent_petri("execute_path");
}



void MainWindow::execut_path()
{
    if (on_point == size) on_point = 0;

    float target_x = X_points.at(on_point);
    float target_y = Y_points.at(on_point);

    on_point++;

    send_goal(target_x, target_y);
}



void MainWindow::execut_point()
{
    float target_x = ui->doubleSpinBox_targetX->value();
    float target_y = ui->doubleSpinBox_targetY->value();
    send_goal(target_x, target_y);
}



void MainWindow::send_goal(float point_x, float point_y)
{
    // Проверка связи с сервером действия
    QMetaObject::invokeMethod(this, [this](){});
    if (!action_client->wait_for_action_server(std::chrono::seconds(2)))
    {
        ui->lineEdit_status->setText("Нет связи с сервером действия");
        return;
    }

    auto goal_msg = MoveToPoint::Goal();
    goal_msg.target_point.x = point_x;
    goal_msg.target_point.y = point_y;

    QString text = "Идем к точке: ( " + QString::number(point_x) + " ; " + QString::number(point_y) + " )";
    // ui->lineEdit_status->setText(text);
    ui->textEdit_log->append(text);


    auto send_goal_options = rclcpp_action::Client<MoveToPoint>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&MainWindow::goal_responce_callback, this, std::placeholders::_1);
    send_goal_options.feedback_callback = std::bind(&MainWindow::feedback_callback, this, std::placeholders::_1, std::placeholders::_2);
    send_goal_options.result_callback = std::bind(&MainWindow::result_callback, this, std::placeholders::_1);

    action_client->async_send_goal(goal_msg, send_goal_options);
}



void MainWindow::on_pushButton_sendCancel_clicked()
{
    send_cancel();
}



void MainWindow::on_pushButton_cancelMisson_clicked()
{
    // processEvent_fsm("cancel");
    (ui->comboBox_chooseMethod->currentIndex() == 0) ? this->processEvent_fsm("cancel") : this->processEvent_petri("cancel");
    send_cancel();
}



void MainWindow::send_cancel()
{
    // Проверка связи с сервером действия
    QMetaObject::invokeMethod(this, [this](){});
    if (!action_client->wait_for_action_server(std::chrono::seconds(2)))
    {
        ui->lineEdit_status->setText("Нет связи с сервером действия");
        return;
    }
    // action_clien->async_cancel_goal(current_goal_handle);
    action_client->async_cancel_all_goals();
}



void MainWindow::on_pushButton_loadPoints_clicked()
{
    X_points.clear();
    Y_points.clear();

    QString test;
    test = "Загрузка пути";
    ui->textEdit_log->append(test);

    QString file_path = ui->lineEdit_pointSource->text();
    // Открываем файл
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->lineEdit_status->setText("Error while openning file");
        return;
    }
    // Если файл открылся, извлекаем из него текст
    QTextStream in(&file);
    // Считываем заголовок и проверяем
    if(!in.atEnd())
    {
        QString line = in.readLine(); // Считываем строку
        QStringList headers = line.split(","); // Разделяем строку по разделителю
        // Проверяем содержимое строки
        if (headers.size() == 2)
        {
            if (headers.at(0) != "X" || headers.at(1) != "Y")
            {
                ui->lineEdit_status->setText("Неверный формат файла");
                return;
            }
        }
    }
    // Считываем отсавшиеся строки
    while(!in.atEnd()) // Пока не достигнем конца файла
    {
        QString line = in.readLine();

        // Если строка не пустая
        if (!line.trimmed().isEmpty())
        {
            QStringList row = line.split(",");
            if(row.size() == 2)
            {
                float x = row.at(0).toFloat();
                float y = row.at(1).toFloat();
                test = "    Точка_" + QString::number(X_points.size() + 1) + ": ( " + QString::number(x) + " ; " + QString::number(y) + " )";
                X_points.push_back(x);
                Y_points.push_back(y);
                ui->textEdit_log->append(test);
            }
            else
            {
                ui->lineEdit_status->setText("Что-то не так");
            }
        }
    }
    if(X_points.size()>=4)
    {
        size = X_points.size();
        path_ready = true;
    }
    else
    {
        ui->lineEdit_status->setText("Мало точек");
    }
}

void MainWindow::processEvent_fsm(QString event)
{
    State_fsm next_state = current_state_fsm;
    bool changed = false;

    if(current_state_fsm == waiting && event == "execute_point")
    {
        next_state = executing_point;
        changed = true;
    }
    else if(current_state_fsm == waiting && event == "execute_path" && path_ready)
    {
        next_state = executing_path;
        changed = true;
    }
    else if(current_state_fsm == executing_path && event == "cancel")
    {
        next_state = waiting;
        changed = true;
    }
    else if(current_state_fsm == executing_point && (event == "cancel" || event == "succeeded"))
    {
        next_state = waiting;
        changed = true;
    }
    else if((current_state_fsm == executing_path || current_state_fsm == executing_point) && event == "error")
    {
        next_state = error;
        changed = true;
    }
    else if(event == "reset")
    {
        next_state = waiting;
        changed = true;
    }

    if(changed)
    {
        current_state_fsm = next_state;
        do_thing();
    }
}

void MainWindow::processEvent_petri(QString event)
{
    bool fire = false;

    if (current_state_petri.waiting && event == "execute_point") {
        current_state_petri.waiting = false;
        current_state_petri.executing_point = true;
        fire = true;
    }
    else if (current_state_petri.waiting && event == "execute_path" && path_ready) {
        current_state_petri.waiting = false;
        current_state_petri.executing_path = true;
        fire = true;
    }
    else if (current_state_petri.executing_path && event == "cancel") {
        current_state_petri.executing_path = false;
        current_state_petri.waiting = true;
        fire = true;
    }
    else if (current_state_petri.executing_point && (event == "cancel" || event == "succeeded")) {
        current_state_petri.executing_point = false;
        current_state_petri.waiting = true;
        fire = true;
    }
    else if ((current_state_petri.executing_path || current_state_petri.executing_point) && event == "error") {
        current_state_petri.executing_path = false;
        current_state_petri.executing_point = false;
        current_state_petri.error = true;
        fire = true;
    }
    else if (event == "reset") {
        current_state_petri.waiting = false;
        current_state_petri.executing_point = false;
        current_state_petri.executing_path = false;
        current_state_petri.error = false;
        current_state_petri.waiting = true;
        fire = true;
    }

    if (fire) {
        do_thing();  // вызываем действие при изменении разметки
    }


}



void MainWindow::do_thing()
{
    QString style = "font-weight: blod;"
                    "color: white;"
                    "border-radius: 10px;";

    if (ui->comboBox_chooseMethod->currentIndex() == 0)
    {
        switch(current_state_fsm)
        {
        case waiting:
            ui->label_statusIndicator->setText("Ожидание...");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: grey;");
            ui->comboBox_chooseMethod->setEnabled(true);
            break;
        case executing_point:
            ui->label_statusIndicator->setText("Точка");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: green;");
            ui->comboBox_chooseMethod->setEnabled(false);
            execut_point();
            break;
        case executing_path:
            ui->label_statusIndicator->setText("Путь");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: green;");
            ui->comboBox_chooseMethod->setEnabled(false);
            execut_path();
            break;
        case error:
            ui->label_statusIndicator->setText("Ошибка");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: red;");
            ui->comboBox_chooseMethod->setEnabled(false);
            break;
        }
    }
    else
    {
        if (current_state_petri.waiting)
        {
            ui->label_statusIndicator->setText("Ожидание...");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: grey;");
            ui->comboBox_chooseMethod->setEnabled(true);
        }
        else if (current_state_petri.executing_point)
        {
            ui->label_statusIndicator->setText("Точка");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: green;");
            ui->comboBox_chooseMethod->setEnabled(false);
            execut_point();
        } else if (current_state_petri.executing_path)
        {
            ui->label_statusIndicator->setText("Путь");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: green;");
            ui->comboBox_chooseMethod->setEnabled(false);
            execut_path();
        } else if (current_state_petri.error)
        {
            ui->label_statusIndicator->setText("Ошибка");
            ui->label_statusIndicator->setStyleSheet(style + "background-color: red;");
            ui->comboBox_chooseMethod->setEnabled(false);
        }
    }
}


void MainWindow::on_comboBox_chooseMethod_currentIndexChanged(int index)
{
    if(ui->comboBox_chooseMethod->currentIndex() == 0 )
    {
        ui->lineEdit_status->setText("Выбран конечный автомат");
    }
    else
    {
        ui->lineEdit_status->setText("Выбран сеть Петри");
    }
}

