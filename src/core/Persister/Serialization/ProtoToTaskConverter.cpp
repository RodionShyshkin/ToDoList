//
// Created by rodion on 9/26/20.
//

#include "ProtoToTaskConverter.h"

ModelTaskDTO ProtoToTaskConverter::ConvertProtoToModelDTO(const TaskProto &task) {
  if(task.deadline() == 0) {
    return ModelTaskDTO::createWithoutParent(TaskID{0}, task.name(), task.label(),
                                             ProtoToTaskConverter::ConvertProtoToPriority(task.priority()),
                                             Date{boost::gregorian::date{task.deadline()}}, task.completed());
  }
  return ModelTaskDTO::createWithParent(TaskID{0}, task.name(), task.label(),
                                           ProtoToTaskConverter::ConvertProtoToPriority(task.priority()),
                                           Date{boost::gregorian::date{task.deadline()}}, task.completed(),
                                           TaskID{task.parent_id()});
}

Priority ProtoToTaskConverter::ConvertProtoToPriority(const TaskProto_Priority &priority) {
  if(TaskProto_Priority_EMPTY == priority) return Priority::EMPTY;
  else if(TaskProto_Priority_LOW == priority) return Priority::LOW;
  else if(TaskProto_Priority_MEDIUM == priority) return Priority::MEDIUM;
  else if(TaskProto_Priority_HIGH == priority) return Priority::HIGH;
  throw std::runtime_error("Invalid priority deserialization.");
}