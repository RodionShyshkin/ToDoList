//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskService.h"

using Pointer = std::shared_ptr<TaskEntity>;
using Vector = std::vector<TaskDTO>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskService::TaskService() : task_service_storage_(TaskServiceStorage()) {}

std::vector<TaskDTO> TaskService::getAllTasks() {
  return task_service_storage_.getAllTasks();
}

std::vector<TaskDTO> TaskService::getTasksForToday() {
  return task_service_storage_.getTasksForToday();
}

std::vector<TaskDTO> TaskService::getTasksForWeek() {
  return task_service_storage_.getTasksForWeek();
}

std::vector<TaskDTO> TaskService::getTasksForLabel(const std::string &label) {
  return task_service_storage_.getTasksForLabel(label);
}

OperationResult TaskService::addTask(const Task &task) {
  return task_service_storage_.AddTask(task);
}

OperationResult TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  return task_service_storage_.AddSubtask(id, subtask);
}
