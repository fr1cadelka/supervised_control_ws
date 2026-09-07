// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from move_to_point_action:action/MoveToPoint.idl
// generated code does not contain a copyright notice

#ifndef MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__BUILDER_HPP_
#define MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "move_to_point_action/action/detail/move_to_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_Goal_target_point
{
public:
  Init_MoveToPoint_Goal_target_point()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::move_to_point_action::action::MoveToPoint_Goal target_point(::move_to_point_action::action::MoveToPoint_Goal::_target_point_type arg)
  {
    msg_.target_point = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_Goal>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_Goal_target_point();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_Result_success
{
public:
  Init_MoveToPoint_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::move_to_point_action::action::MoveToPoint_Result success(::move_to_point_action::action::MoveToPoint_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_Result>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_Result_success();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_Feedback_progress
{
public:
  Init_MoveToPoint_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::move_to_point_action::action::MoveToPoint_Feedback progress(::move_to_point_action::action::MoveToPoint_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_Feedback>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_Feedback_progress();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_SendGoal_Request_goal
{
public:
  explicit Init_MoveToPoint_SendGoal_Request_goal(::move_to_point_action::action::MoveToPoint_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::move_to_point_action::action::MoveToPoint_SendGoal_Request goal(::move_to_point_action::action::MoveToPoint_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_SendGoal_Request msg_;
};

class Init_MoveToPoint_SendGoal_Request_goal_id
{
public:
  Init_MoveToPoint_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPoint_SendGoal_Request_goal goal_id(::move_to_point_action::action::MoveToPoint_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveToPoint_SendGoal_Request_goal(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_SendGoal_Request>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_SendGoal_Request_goal_id();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_SendGoal_Response_stamp
{
public:
  explicit Init_MoveToPoint_SendGoal_Response_stamp(::move_to_point_action::action::MoveToPoint_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::move_to_point_action::action::MoveToPoint_SendGoal_Response stamp(::move_to_point_action::action::MoveToPoint_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_SendGoal_Response msg_;
};

class Init_MoveToPoint_SendGoal_Response_accepted
{
public:
  Init_MoveToPoint_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPoint_SendGoal_Response_stamp accepted(::move_to_point_action::action::MoveToPoint_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveToPoint_SendGoal_Response_stamp(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_SendGoal_Response>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_SendGoal_Response_accepted();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_GetResult_Request_goal_id
{
public:
  Init_MoveToPoint_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::move_to_point_action::action::MoveToPoint_GetResult_Request goal_id(::move_to_point_action::action::MoveToPoint_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_GetResult_Request>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_GetResult_Request_goal_id();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_GetResult_Response_result
{
public:
  explicit Init_MoveToPoint_GetResult_Response_result(::move_to_point_action::action::MoveToPoint_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::move_to_point_action::action::MoveToPoint_GetResult_Response result(::move_to_point_action::action::MoveToPoint_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_GetResult_Response msg_;
};

class Init_MoveToPoint_GetResult_Response_status
{
public:
  Init_MoveToPoint_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPoint_GetResult_Response_result status(::move_to_point_action::action::MoveToPoint_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveToPoint_GetResult_Response_result(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_GetResult_Response>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_GetResult_Response_status();
}

}  // namespace move_to_point_action


namespace move_to_point_action
{

namespace action
{

namespace builder
{

class Init_MoveToPoint_FeedbackMessage_feedback
{
public:
  explicit Init_MoveToPoint_FeedbackMessage_feedback(::move_to_point_action::action::MoveToPoint_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::move_to_point_action::action::MoveToPoint_FeedbackMessage feedback(::move_to_point_action::action::MoveToPoint_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_FeedbackMessage msg_;
};

class Init_MoveToPoint_FeedbackMessage_goal_id
{
public:
  Init_MoveToPoint_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPoint_FeedbackMessage_feedback goal_id(::move_to_point_action::action::MoveToPoint_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveToPoint_FeedbackMessage_feedback(msg_);
  }

private:
  ::move_to_point_action::action::MoveToPoint_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_to_point_action::action::MoveToPoint_FeedbackMessage>()
{
  return move_to_point_action::action::builder::Init_MoveToPoint_FeedbackMessage_goal_id();
}

}  // namespace move_to_point_action

#endif  // MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__BUILDER_HPP_
