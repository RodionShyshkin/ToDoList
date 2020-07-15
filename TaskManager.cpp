//
// Created by rodion on 7/15/20.
//

#include "TaskManager.h"

TaskManager::TaskManager() = default;
TaskManager::~TaskManager() = default;

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
  else {
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

void TaskManager::addSubtask(Task &root, Task &subtask) {
  auto root_ptr = std::make_shared<Task>(root);
  for (auto task : tasks) {
    if (task->getName() == root_ptr->getName()) {
      subtask.setRoot(task);
      task->pushSubtask(subtask);
      addTask(subtask);
      return;
    }
  }
}

void TaskManager::markTask(const Task& taskToMark) {
  auto task_ptr = std::make_shared<Task>(taskToMark);
  for(auto task : tasks) {
    if(task->getName() == task_ptr->getName()) {
      task->setStatus();
      return;
    }
  }
}