//
// Created by rodion on 8/10/20.
//

#include "TaskServiceStorage.h"

TaskServiceStorage::TaskServiceStorage() : generate_id_(GenerateID()) {}

std::vector<TaskDTO> TaskServiceStorage::getAllTasks() {
  auto tasks = task_view_.getAllTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task.getID(), task.getTask(), task.getStatus()));

  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::getTasksForToday() {
  auto tasks = task_view_.getTodayTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task.getID(), task.getTask(), task.getStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::getTasksForWeek() {
  auto tasks = task_view_.getWeekTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task.getID(), task.getTask(), task.getStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::getTasksForName(const std::string &name) {
  auto tasks = task_view_.getTasksByName(name);
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task.getID(), task.getTask(), task.getStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::getTasksForLabel(const std::string &label) {
  auto tasks = task_view_.getTasksByLabel(label);
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO(task.getID(), task.getTask(), task.getStatus()));
  }
  return searchResult;
}

std::optional<TaskDTO> TaskServiceStorage::getTaskByID(const TaskID &id) {
  auto task = task_storage_.getTask(id);
  if(task.has_value()) {
    return TaskDTO(task.value()->getID(), task.value()->getTask(), task.value()->getStatus());
  }
  return std::nullopt;
}

std::optional<TaskDTO> TaskServiceStorage::AddTask(const Task &task) {
  auto newid = generate_id_.generateID();
  auto newtask = TaskEntity(task, newid);
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  task_storage_.pushTask(std::make_pair(newid, task_ptr));
  task_view_.addTask(task_ptr);

  if(newid.get_id() > 9999) return std::nullopt;
  return TaskDTO(newid, task, newtask.getStatus());
}

std::optional<TaskDTO> TaskServiceStorage::AddSubtask(const TaskID &id, const Task &subtask) {
  auto task = task_storage_.getTask(id);
  if(!task.has_value()) return std::nullopt;

  auto newid = generate_id_.generateID();
  auto newtask = TaskEntity(subtask, newid);
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  task_storage_.pushTask(std::make_pair(newid, task_ptr));
  task_view_.addTask(task_ptr);
  task.value()->AddSubtask(task_ptr);

  if(newid.get_id() > 9999) return std::nullopt;
  return TaskDTO(newid, subtask, newtask.getStatus());
}