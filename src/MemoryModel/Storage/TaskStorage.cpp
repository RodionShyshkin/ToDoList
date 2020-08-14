//
// Created by rodion on 8/2/20.
//

#include "TaskStorage.h"

bool TaskStorage::PushTask(const std::shared_ptr<TaskEntity>& task) {
  auto pair = std::make_pair(task->GetID(), task);
  if(tasks_.find(pair.first) != tasks_.end()) return false;
  tasks_.insert(pair);
  return true;
}

bool TaskStorage::RemoveTask(const TaskID &id) {
  auto task = tasks_.find(id);
  if(task == tasks_.end()) return false;
  tasks_.erase(task);
  return true;
}

std::shared_ptr<TaskEntity> TaskStorage::GetTask(const TaskID &id) {
  for(auto [ID, task] : tasks_) {
    if(ID == id) return task;
  }
  return nullptr;
}

bool TaskStorage::HasTask(const TaskID &id) {
  return (tasks_.find(id) != tasks_.end());
}
