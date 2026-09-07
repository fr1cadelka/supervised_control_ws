#include <QCoreApplication>
#include <thread>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    rclcpp::init(argc, argv);

    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>("gui_node"); // Имя узла

    MainWindow m(node);
    m.show();
    // Запуск отдельного потока через лябда функцию
    std::thread ros_thread ([node]()
                           {
                               rclcpp::spin(node);
                           });
    int result = app.exec();
    rclcpp::shutdown();
    ros_thread.join();
    return result;
}
