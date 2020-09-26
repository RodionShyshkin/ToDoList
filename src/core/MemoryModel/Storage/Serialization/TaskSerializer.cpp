//
// Created by rodion on 9/25/20.
//

#include "TaskSerializer.h"

TaskProto TaskSerializer::SerializeTaskWithSubtasks(const TaskEntity &task) {
  auto* newtask = new TaskProto;
  newtask = TaskSerializer::SerializeTask(task);
  for(const auto& [first, second] : task.GetSubtasks()) {
    auto subtask_ptr = newtask->add_subtasks();
    auto subtask = *second.lock();
    TaskSerializer::SetTaskProtoFields(subtask_ptr, subtask);
  }
  return *newtask;
}

TaskProto* TaskSerializer::SerializeTask(const TaskEntity &task) {
  auto* newtask = new TaskProto;
  TaskSerializer::SetTaskProtoFields(newtask, task);
  return newtask;
}

TaskProto_Priority TaskSerializer::SerializePriority(const Priority &priority) {
  if(Priority::EMPTY == priority) return TaskProto_Priority_EMPTY;
  else if(Priority::LOW == priority) return TaskProto_Priority_LOW;
  else if(Priority::MEDIUM == priority) return TaskProto_Priority_MEDIUM;
  else if(Priority::HIGH == priority) return TaskProto_Priority_HIGH;
  throw std::runtime_error("Invalid priority serialization.");
}

void TaskSerializer::SetTaskProtoFields(TaskProto *task, const TaskEntity& task_entity) {
  task->set_name(task_entity.GetName());
  task->set_label(task_entity.GetLabel());
  task->set_priority(TaskSerializer::SerializePriority(task_entity.GetPriority()));
  task->set_deadline(task_entity.GetDueTime().GetDate().day_number());
  task->set_completed(task_entity.GetStatus());

  auto parent = task_entity.GetParentID();
  if(parent == task_entity.GetID()) task->set_parent_id(0);
    else task->set_parent_id(parent.GetID());
}