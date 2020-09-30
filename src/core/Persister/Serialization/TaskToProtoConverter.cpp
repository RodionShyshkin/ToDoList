//
// Created by rodion on 9/25/20.
//

#include "TaskToProtoConverter.h"

TaskProto TaskToProtoConverter::ConvertTaskEntityToProto(const ModelTaskDTO &task) {
  auto newtask = std::make_unique<TaskProto>();
  TaskToProtoConverter::SetTaskProtoFields(newtask.get(), task);
  return *newtask;
 /*
  newtask = TaskToProtoConverter::ConvertSingleTask(task);
  for(const auto& [first, second] : task.GetSubtasks()) {
    auto subtask_ptr = newtask->add_subtasks();
    auto subtask = *second.lock();
    TaskToProtoConverter::SetTaskProtoFields(subtask_ptr, subtask);
  }
  return *newtask;*/
}

std::unique_ptr<TaskProto> TaskToProtoConverter::ConvertSingleTask(const ModelTaskDTO &task) {
  auto newtask = std::make_unique<TaskProto>();
  TaskToProtoConverter::SetTaskProtoFields(newtask.get(), task);
  return std::move(newtask);
}

TaskProto_Priority TaskToProtoConverter::ConvertPriority(const Priority &priority) {
  if(Priority::EMPTY == priority) return TaskProto_Priority_EMPTY;
  else if(Priority::LOW == priority) return TaskProto_Priority_LOW;
  else if(Priority::MEDIUM == priority) return TaskProto_Priority_MEDIUM;
  else if(Priority::HIGH == priority) return TaskProto_Priority_HIGH;
  throw std::runtime_error("Invalid priority serialization.");
}

void TaskToProtoConverter::SetTaskProtoFields(TaskProto* task, const ModelTaskDTO& task_entity) {
  task->set_name(task_entity.getName());
  task->set_label(task_entity.getLabel());
  task->set_priority(TaskToProtoConverter::ConvertPriority(task_entity.getPriority()));
  task->set_deadline(task_entity.getDueDate().GetDate().day_number());
  task->set_completed(task_entity.getStatus());

  auto parent = task_entity.getParentID();
  if(parent == task_entity.getID()) task->set_parent_id(0);
    else task->set_parent_id(parent.GetID());
}