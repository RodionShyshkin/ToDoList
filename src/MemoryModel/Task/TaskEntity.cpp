//
// Created by rodion on 7/16/20.
//

#include "TaskEntity.h"

TaskEntity::TaskEntity() = default;

TaskEntity::TaskEntity(const Task &task, const TaskID &id, const TaskID& parent) {
  this->user_id_ = id;
  this->task_ = task;
  this->status_ = false;
  this->parent_id_ = parent;
}

TaskEntity TaskEntity::createTask(const Task &task, const TaskID &id) {
  return TaskEntity(task, id, id);
}

TaskEntity TaskEntity::createSubtask(const Task &task, const TaskID &id, const TaskID &parent) {
  return TaskEntity(task, id, parent);
}

TaskID TaskEntity::GetID() const { return user_id_; }

std::string TaskEntity::GetName() const { return task_.GetName(); }

std::string TaskEntity::GetLabel() const { return task_.GetLabel(); }

Priority TaskEntity::GetPriority() const { return task_.GetPriority(); }

Date TaskEntity::GetDueTime() const { return task_.GetDate(); }

bool TaskEntity::GetStatus() const { return status_; }

Task TaskEntity::GetTask() const { return task_; }

std::map<TaskID, std::weak_ptr<TaskEntity>> TaskEntity::GetSubtasks() const { return subtasks_; }

TaskID TaskEntity::GetParentID() const { return parent_id_; }


void TaskEntity::AddSubtask(const std::weak_ptr<TaskEntity> &task) {
  subtasks_.insert(std::make_pair(task.lock()->GetID(), task));
}

bool TaskEntity::RemoveSubtask(const TaskID &id) {
  auto subtaskToRemove = subtasks_.find(id);
  if(subtaskToRemove == subtasks_.end()) return false;
  subtasks_.erase(subtaskToRemove);
  return true;
}

bool TaskEntity::checkParent() {
  if(parent_id_ == user_id_) return false;
  return true;
}

bool TaskEntity::SetComplete() {
  if(this->status_) return false;
  this->status_ = true;
  return true;
}

bool TaskEntity::SubstituteTask(const Task &newtask) {
  if(newtask.GetDate().GetDate() < this->GetDueTime()) return false;
  this->task_ = newtask;
  return true;
}