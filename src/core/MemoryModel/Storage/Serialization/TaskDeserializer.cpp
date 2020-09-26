//
// Created by rodion on 9/26/20.
//

#include "TaskDeserializer.h"

std::shared_ptr<TaskEntity> TaskDeserializer::DeserializeTask(const TaskProto &task) {
  auto task_ = Task::create(task.name(), task.label(),
                            TaskDeserializer::DeserializePriority(task.priority()),
                            boost::gregorian::date{task.deadline()});
  if(!task_.has_value()) return nullptr;
  TaskEntity entity = TaskEntity::createTask(task_.value(), TaskID{0});
  if(task.completed()) entity.SetComplete();
  return std::make_shared<TaskEntity>(entity);
}

Priority TaskDeserializer::DeserializePriority(const TaskProto_Priority &priority) {
  if(TaskProto_Priority_EMPTY == priority) return Priority::EMPTY;
  else if(TaskProto_Priority_LOW == priority) return Priority::LOW;
  else if(TaskProto_Priority_MEDIUM == priority) return Priority::MEDIUM;
  else if(TaskProto_Priority_HIGH == priority) return Priority::HIGH;
  throw std::runtime_error("Invalid priority deserialization.");
}