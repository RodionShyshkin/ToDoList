//
// Created by rodion on 7/15/20.
//

#include "TaskManager.h"

TaskManager::TaskManager() = default;
TaskManager::~TaskManager() = default;

void TaskManager::showAllTasks() const {
  for(auto item : tasks) {
//    std::cout << *item << std::endl;
    item->showTask();
  }
  if(tasks.empty()) std::cout << "Vector is empty" << std::endl;

  for(auto [key, value] : sortedTasks) {
    value->showTask();
  }
}

void TaskManager::addTask(std::shared_ptr<Task> task) {
  Priority temp = task->getPriority();
  std::cout << temp << std::endl;
  tasks.push_back(task);


  sortedTasks.insert(std::pair<Priority, std::shared_ptr<Task>>(task->getPriority(), task));
}