//
// Created by rodion on 7/23/20.
//

#include "TaskManagerDTO.h"

TaskManagerDTO::TaskManagerDTO(const std::shared_ptr<TaskManager> &dir) : dir(dir) {}

TaskManagerDTO::~TaskManagerDTO() = default;

size_t TaskManagerDTO::getTasksAmount() const { return dir->tasks.size(); }

std::vector<std::shared_ptr<FullTask>> TaskManagerDTO::getAllTasks() const { return dir->tasks; }

FullTaskDTO TaskManagerDTO::getTask(const TaskID &userid) const {
  for(auto task : dir->tasks) {
    if(task->getUserID() == userid) return task;
  }
}
