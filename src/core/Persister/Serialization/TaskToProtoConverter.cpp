//
// Created by rodion on 9/25/20.
//

#include "TaskToProtoConverter.h"

TaskProto TaskToProtoConverter::ConvertTaskEntityToProto(const TaskEntity &task) {
  auto newtask = std::make_unique<TaskProto>();
  newtask = TaskToProtoConverter::ConvertSingleTask(task);
  for(const auto& [first, second] : task.GetSubtasks()) {
    auto subtask_ptr = newtask->add_subtasks();
    auto subtask = *second.lock();
    TaskToProtoConverter::SetTaskProtoFields(subtask_ptr, subtask);
  }
  return *newtask;
}

std::unique_ptr<TaskProto> TaskToProtoConverter::ConvertSingleTask(const TaskEntity &task) {
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

void TaskToProtoConverter::SetTaskProtoFields(TaskProto* task, const TaskEntity& task_entity) {
  task->set_name(task_entity.GetName());
  task->set_label(task_entity.GetLabel());
  task->set_priority(TaskToProtoConverter::ConvertPriority(task_entity.GetPriority()));
  task->set_deadline(task_entity.GetDueTime().GetDate().day_number());
  task->set_completed(task_entity.GetStatus());

  auto parent = task_entity.GetParentID();
  if(parent == task_entity.GetID()) task->set_parent_id(0);
    else task->set_parent_id(parent.GetID());
}