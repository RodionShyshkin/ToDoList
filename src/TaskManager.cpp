//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskManager.h"

using Pointer = std::shared_ptr<FullTask>;
using Vector = std::vector<Pointer>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskManager::TaskManager() : newID() {}
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
  Vector searchResult;
  for (auto[priority, sortingTask] : sortedTasks) {
    if (sortingTask->getLabel() == label) {
      searchResult.push_back(sortingTask);
    }
  }
  if (searchResult.size() == 0) std::cout << "No tasks found." << std::endl;
  else {
    std::cout << searchResult.size() << " tasks found." << std::endl;
    for (auto itemTask : searchResult) itemTask->showTask();
  }
}

void TaskManager::addTask(const Task &task) {
  auto task_ptr = std::make_shared<FullTask>(task, newID.generateID());
  tasks.push_back(task_ptr);
  sortedTasks.insert(std::pair<Task::Priority, std::shared_ptr<FullTask>>(task.getPriority(), task_ptr));
}

void TaskManager::addSubtask(const TaskID &id, const Task &subtask) {
  for (auto task : tasks) {
    if (task->getID() == id) {
      auto subptr = std::make_shared<FullTask>(subtask, id);
      task->AddSubtask(subptr);
      addTask(subtask);
      return;
    }
  }
}

void TaskManager::removeTask(const unsigned int &id) {
}

void TaskManager::markTask(const unsigned int &id) {
//  auto task_ptr = std::make_shared<Task>(taskToMark);
  for(auto itemTask : tasks) {
    if(itemTask->getID() == id) {
      itemTask->setComplete();
      return;
    }
  }
}