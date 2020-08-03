//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskService.h"

using Pointer = std::shared_ptr<TaskEntity>;
using Vector = std::vector<TaskDTO>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskService::TaskService() : task_factory_(TaskFactory()) {}
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
  task_view_.addTask(task_factory_.addTask(task));
}

bool TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  auto task = task_factory_.addSubtask(id, subtask);
  if(task.has_value()) {
    task_view_.addTask(task.value());
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