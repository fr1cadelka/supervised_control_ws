#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <std_srvs/srv/empty.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <move_to_point_action/action/move_to_point.hpp>
#include <memory>

#include <QFile>
#include <QTextStream>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

enum State_fsm{waiting, executing_point, executing_path, error};

struct PetriNetState
{
    bool waiting;
    bool executing_point;
    bool executing_path;
    bool error;
};

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(rclcpp::Node::SharedPtr n, QWidget *parent = nullptr);
    ~MainWindow();
    // Для удобства используем локальные сокращения
    using MoveToPoint = move_to_point_action::action::MoveToPoint;
    using GoalHandleMoveToPoint = rclcpp_action::ClientGoalHandle<MoveToPoint>;
private slots:
    void on_comboBox_chooseMethod_currentIndexChanged(int index);

private slots:
    void on_pushButton_startMisson_clicked();

private slots:
    void on_pushButton_cancelMisson_clicked();

private slots:
    void on_pushButton_loadPoints_clicked();

private slots:
    void on_pushButton_sendToGoal_clicked();

private slots:
    void on_pushButton_reset_clicked();
    void on_pushButton_sendCancel_clicked();

private:
    Ui::MainWindow *ui;
    rclcpp::Node::SharedPtr node;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr reset_srv;
    rclcpp_action::Client<MoveToPoint>::SharedPtr action_client;

    State_fsm current_state_fsm;
    bool path_ready;

    QVector<float> X_points;
    QVector<float> Y_points;
    int size;
    int on_point{0};

    PetriNetState current_state_petri;

    void processEvent_fsm(QString event);
    void processEvent_petri(QString event);
    void send_goal(float point_x, float point_y);
    void send_cancel();

    void do_thing();

    void execut_path();
    void execut_point();

    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg);

    //  Функция обратного вызова для действия
    void goal_responce_callback(const GoalHandleMoveToPoint::SharedPtr &goal_handle);
    void feedback_callback(GoalHandleMoveToPoint::SharedPtr, const std::shared_ptr<const MoveToPoint::Feedback> feedback);
    void result_callback(const GoalHandleMoveToPoint::WrappedResult &result);
};

#endif // MAINWINDOW_H
