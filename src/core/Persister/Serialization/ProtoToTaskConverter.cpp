//
// Created by rodion on 9/26/20.
//

#include "ProtoToTaskConverter.h"

std::optional<TaskEntity> ProtoToTaskConverter::UnconvertTask(const TaskProto &task) {
  auto task_ = Task::create(task.name(), task.label(),
                            ProtoToTaskConverter::UnconvertPriority(task.priority()),
                            boost::gregorian::date{task.deadline()});
  if(!task_.has_value()) return std::nullopt;
  TaskEntity entity = TaskEntity::createTask(task_.value(), TaskID{0});
  if(task.completed()) entity.SetComplete();
  return entity;
//  return std::make_shared<TaskEntity>(entity);
}

Priority ProtoToTaskConverter::UnconvertPriority(const TaskProto_Priority &priority) {
  if(TaskProto_Priority_EMPTY == priority) return Priority::EMPTY;
  else if(TaskProto_Priority_LOW == priority) return Priority::LOW;
  else if(TaskProto_Priority_MEDIUM == priority) return Priority::MEDIUM;
  else if(TaskProto_Priority_HIGH == priority) return Priority::HIGH;
  throw std::runtime_error("Invalid priority deserialization.");
}