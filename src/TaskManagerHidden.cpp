//
// Created by rodion on 7/23/20.
//

#include "TaskManagerHidden.h"

TaskManagerHidden::TaskManagerHidden(const std::shared_ptr<TaskManager> &dir) : dir(dir) {}

TaskManagerHidden::~TaskManagerHidden() = default;

size_t TaskManagerHidden::getTasksAmount() const { return dir->tasks.size(); }

std::vector<FullTaskDTO> TaskManagerHidden::getAllTasks() const {
  return dir->tasks;
}

FullTaskDTO TaskManagerHidden::getTask(const TaskID &userid) const {
  for(auto task : dir->tasks) {
    if(task.getUserID() == userid) return task;
  }
}
