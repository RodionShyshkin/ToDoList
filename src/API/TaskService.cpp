//
// Created by rodion on 7/15/20.
//

#include "TaskService.h"

TaskService::TaskService() : task_service_storage_(FullStorage()) {}

std::vector<TaskDTO> TaskService::getAllTasks() {
  auto allTasks = task_service_storage_.GetTaskView().GetAllTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : allTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday() {
  auto todayTasks = task_service_storage_.GetTaskView().GetTodayTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : todayTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek() {
  auto weekTasks = task_service_storage_.GetTaskView().GetWeekTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : weekTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByLabel(const std::string &label) {
  auto labelTasks = task_service_storage_.GetTaskView().GetTasksByLabel(label);
  std::vector<TaskDTO> searchResult;
  for(auto task : labelTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

OperationResult TaskService::addTask(const Task &task) {
  return task_service_storage_.AddTask(task);
}

OperationResult TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  return task_service_storage_.AddSubtask(id, subtask);
}

OperationResult TaskService::RemoveTask(const TaskID &id) {
  return task_service_storage_.RemoveTask(id);
}

std::vector<TaskEntity> TaskService::getDebug() {
  return task_service_storage_.GetTaskView().GetAllTasks();
}

TaskStorage TaskService::getDebug2() {
  return task_service_storage_.GetTaskStorage();
}


