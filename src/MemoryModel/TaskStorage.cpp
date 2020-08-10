//
// Created by rodion on 8/2/20.
//

#include "TaskStorage.h"

void TaskStorage::pushTask(const std::pair<TaskID, std::shared_ptr<TaskEntity> >& task) {
  if(task.first == task.second->getID()) tasks_.insert(task);
  else throw std::invalid_argument("IDs are not equal.");
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorage::getTask(const TaskID &id) {
  for(auto [ID, task] : tasks_) {
    if(ID == id) return task;
  }
  return std::nullopt;
}

bool TaskStorage::if_exist(const TaskID &id) {
  if(tasks_.find(id) != tasks_.end()) return true; else return false;
}
