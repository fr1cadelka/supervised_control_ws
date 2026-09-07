// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from move_to_point_action:action/MoveToPoint.idl
// generated code does not contain a copyright notice

#ifndef MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__STRUCT_H_
#define MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target_point'
#include "geometry_msgs/msg/detail/point32__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_Goal
{
  geometry_msgs__msg__Point32 target_point;
} move_to_point_action__action__MoveToPoint_Goal;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_Goal.
typedef struct move_to_point_action__action__MoveToPoint_Goal__Sequence
{
  move_to_point_action__action__MoveToPoint_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_Result
{
  bool success;
} move_to_point_action__action__MoveToPoint_Result;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_Result.
typedef struct move_to_point_action__action__MoveToPoint_Result__Sequence
{
  move_to_point_action__action__MoveToPoint_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_Feedback
{
  float progress;
} move_to_point_action__action__MoveToPoint_Feedback;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_Feedback.
typedef struct move_to_point_action__action__MoveToPoint_Feedback__Sequence
{
  move_to_point_action__action__MoveToPoint_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "move_to_point_action/action/detail/move_to_point__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  move_to_point_action__action__MoveToPoint_Goal goal;
} move_to_point_action__action__MoveToPoint_SendGoal_Request;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_SendGoal_Request.
typedef struct move_to_point_action__action__MoveToPoint_SendGoal_Request__Sequence
{
  move_to_point_action__action__MoveToPoint_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} move_to_point_action__action__MoveToPoint_SendGoal_Response;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_SendGoal_Response.
typedef struct move_to_point_action__action__MoveToPoint_SendGoal_Response__Sequence
{
  move_to_point_action__action__MoveToPoint_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} move_to_point_action__action__MoveToPoint_GetResult_Request;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_GetResult_Request.
typedef struct move_to_point_action__action__MoveToPoint_GetResult_Request__Sequence
{
  move_to_point_action__action__MoveToPoint_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "move_to_point_action/action/detail/move_to_point__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_GetResult_Response
{
  int8_t status;
  move_to_point_action__action__MoveToPoint_Result result;
} move_to_point_action__action__MoveToPoint_GetResult_Response;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_GetResult_Response.
typedef struct move_to_point_action__action__MoveToPoint_GetResult_Response__Sequence
{
  move_to_point_action__action__MoveToPoint_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "move_to_point_action/action/detail/move_to_point__struct.h"

/// Struct defined in action/MoveToPoint in the package move_to_point_action.
typedef struct move_to_point_action__action__MoveToPoint_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  move_to_point_action__action__MoveToPoint_Feedback feedback;
} move_to_point_action__action__MoveToPoint_FeedbackMessage;

// Struct for a sequence of move_to_point_action__action__MoveToPoint_FeedbackMessage.
typedef struct move_to_point_action__action__MoveToPoint_FeedbackMessage__Sequence
{
  move_to_point_action__action__MoveToPoint_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_to_point_action__action__MoveToPoint_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOVE_TO_POINT_ACTION__ACTION__DETAIL__MOVE_TO_POINT__STRUCT_H_
