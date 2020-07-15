//
// Created by rodion on 7/15/20.
//

#include "TaskManager.h"

TaskManager::TaskManager() = default;
TaskManager::~TaskManager() = default;

void TaskManager::showAllTasks() const {
  /*for(auto item : tasks) {
    item->showTask();
  }
  if(tasks.empty()) std::cout << "Vector is empty" << std::endl;*/
  if(sortedTasks.empty()) { std::cout << "No tasks" << std::endl; }
  else {
    for (auto[key, value] : sortedTasks) {
      value->showTask();
    }
  }
}

/*void TaskManager::showTasksForToday() const {
  int today = 99;
  if(sortedTasks.empty()) { std::cout << "no tasks" << std::endl; }
  else {
    std::vector<Task> todayTasks;
    for(auto[priority, task] : sortedTasks) {
      if(task->getDate() == today) {
        todayTasks.push_back(task);
      }
    }
  }
}*/

void TaskManager::addTask(std::shared_ptr<Task> task) {
  tasks.push_back(task);
  sortedTasks.insert(std::pair<Priority, std::shared_ptr<Task>>(task->getPriority(), task));
}