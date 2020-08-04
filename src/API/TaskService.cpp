//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskService.h"

using Pointer = std::shared_ptr<TaskEntity>;
using Vector = std::vector<TaskDTO>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskService::TaskService() : owner_(TaskOwner()) {}
TaskService::~TaskService() = default;


std::vector<TaskDTO> TaskService::getAllTasks() {
  auto tasks = task_view_.getAllTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday() {
  auto tasks = task_view_.getTodayTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek() {
  auto tasks = task_view_.getWeekTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForLabel(const std::string &label) {
  auto tasks = task_view_.getTasksByLabel(label);
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task));
  }
  return searchResult;
}

TaskDTO TaskService::getTaskByID(const TaskID &id) {
  auto tasks = task_view_.getAllTasks();
  for(auto task : tasks) {
    if(task.getUserID() == id) return TaskDTO(task);
  }
}

void TaskService::addTask(const Task &task) {
  auto newid = owner_.generateID();
  auto task_ptr = std::make_shared<TaskEntity>(task, newid);
  owner_.pushTask(std::make_pair(newid, task_ptr));
}

bool TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  if(owner_.if_exist(id)) {
    auto newid = owner_.generateID();
    auto task_ptr = std::make_shared<TaskEntity>(subtask, newid);
    owner_.pushTask(std::make_pair(newid, task_ptr));
    return true;
  }
  return false;
}

/*void TaskService::removeTask(const TaskID &id) {
  auto taskToRemove = std::make_shared<TaskEntity>();
  size_t NumInVector;
  auto IteratorInMultimap = sortedTasks.begin();

  for (auto counter = 0; counter < tasks.size(); counter++) {
    if (tasks[counter]->getUserID() == id) {
      taskToRemove = tasks[counter];
      NumInVector = counter;
      break;
    }
  }
  for (auto it = sortedTasks.begin(); it != sortedTasks.end(); ++it) {
    if (it->second->getUserID() == id) {
      IteratorInMultimap = it;
      break;
    }
  }

  tasks.erase(tasks.begin() + NumInVector);
  sortedTasks.erase(IteratorInMultimap);
}

*/