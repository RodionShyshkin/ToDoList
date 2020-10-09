//
// Created by rodion on 9/25/20.
//

#include "TaskToProtoConverter.h"

TaskProto TaskToProtoConverter::ConvertTaskToProto(const ModelTaskDTO &task) {
  auto newtask = std::make_unique<TaskProto>();
  newtask->set_name(task.getName());
  newtask->set_label(task.getLabel());
  newtask->set_priority(TaskToProtoConverter::ConvertPriorityToProto(task.getPriority()));
  newtask->set_deadline(task.getDueDate().GetDate().day_number());
  newtask->set_completed(task.getStatus());

  auto parent = task.getParentID();
  if(parent == task.getID()) newtask->set_parent_id(0);
  else newtask->set_parent_id(parent.GetID());
  return *newtask;
}

TaskProto_Priority TaskToProtoConverter::ConvertPriorityToProto(const Priority &priority) {
  if(Priority::EMPTY == priority) return TaskProto_Priority_EMPTY;
  else if(Priority::LOW == priority) return TaskProto_Priority_LOW;
  else if(Priority::MEDIUM == priority) return TaskProto_Priority_MEDIUM;
  else if(Priority::HIGH == priority) return TaskProto_Priority_HIGH;
  throw std::runtime_error("Invalid priority serialization.");
}
