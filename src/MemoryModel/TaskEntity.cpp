//
// Created by rodion on 7/16/20.
//

#include "TaskEntity.h"

TaskEntity::TaskEntity() = default;

TaskEntity::TaskEntity(const Task &task, const TaskID &id) {
  this->user_id_ = id;
  this->task_ = task;
  this->status_ = false;
}

TaskEntity TaskEntity::create(const Task &task, const TaskID &id) {
  return TaskEntity(task, id);
}

TaskID TaskEntity::GetID() const { return user_id_; }
std::string TaskEntity::GetName() const { return task_.GetName(); }
std::string TaskEntity::GetLabel() const { return task_.GetLabel(); }
Priority TaskEntity::GetPriority() const { return task_.GetPriority(); }
Date TaskEntity::GetDueTime() const { return task_.GetDate(); }
bool TaskEntity::GetStatus() const { return status_; }
Task TaskEntity::GetTask() const { return task_; }
std::vector<std::shared_ptr<TaskEntity>> TaskEntity::GetSubtasks() const { return subtasks_; }


void TaskEntity::AddSubtask(const std::shared_ptr<TaskEntity> &task) {
  subtasks_.push_back(task);
}
