//
// Created by rodion on 8/2/20.
//

#include "TaskStorage.h"

bool TaskStorage::AddTask(const std::shared_ptr<TaskEntity>& task) {
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
  for(const auto& [ID, task] : tasks_) {
    if(ID == id) return task;
  }
  return nullptr;
}

std::vector<TaskEntity> TaskStorage::GetAllTasks() {
  std::vector<TaskEntity> result;
  for(const auto& [first, second] : this->tasks_) {
    result.push_back(*second);
  }
  return result;
}
