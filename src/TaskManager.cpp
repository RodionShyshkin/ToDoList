//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskManager.h"

TaskManager::TaskManager() = default;
TaskManager::~TaskManager() = default;

bool operator==(const Task &lhs, const Task &rhs) {
  return lhs.getId() == rhs.getId();
}

void TaskManager::showAllTasks() const {
  if (sortedTasks.empty()) { std::cout << "No tasks" << std::endl; }
  else {
    for (auto[key, value] : sortedTasks) {
      value->showTask();
    }
  }
}

/*void TaskManager::showTasksForToday() const {
  int today = 99;
  if(sortedTasks.empty()) { std::cout << "no tasks" << std::endl; }
  lse {
    std::vector<Task> todayTasks;
    for(auto[priority, task] : sortedTasks) {
      if(task->getDate() == today) {
        todayTasks.push_back(task);
      }
    }
  }
}*/

void TaskManager::showTasksForLabel(const std::string &label) const {
  std::vector<std::shared_ptr<Task>> searchResult;
  for (auto[priority, task] : sortedTasks) {
    if (task->getLabel() == label) {
      searchResult.push_back(task);
    }
  }
  if (searchResult.size() == 0) std::cout << "No tasks found." << std::endl;
  else {
    std::cout << searchResult.size() << " tasks found." << std::endl;
    for (auto task : searchResult) task->showTask();
  }
}

void TaskManager::addTask(const Task &task) {
  auto task_ptr = std::make_shared<Task>(task);
  for(auto existTask : tasks) { if(existTask->getId() == task.getId()) return; }
  tasks.push_back(task_ptr);
  sortedTasks.insert(std::pair<Priority, std::shared_ptr<Task>>(task.getPriority(), task_ptr));
}

void TaskManager::addSubtask(const unsigned int &id, Task &subtask) {
  for (auto task : tasks) {
    if (task->getId() == id) {
      subtask.setRoot(task);
      task->pushSubtask(subtask);
      addTask(subtask);
      return;
    }
  }
}

void TaskManager::removeTask(const unsigned int &id) {
}

void TaskManager::markTask(const unsigned int &id) {
//  auto task_ptr = std::make_shared<Task>(taskToMark);
  for(auto task : tasks) {
    if(task->getId() == id) {
      task->setStatus();
      return;
    }
  }
}