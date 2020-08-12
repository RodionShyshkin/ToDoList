//
// Created by rodion on 8/10/20.
//

#include "TaskServiceStorage.h"

TaskServiceStorage::TaskServiceStorage() : generate_id_(IDGenerator()) {}

std::vector<TaskDTO> TaskServiceStorage::GetAllTasks() {
  auto tasks = task_view_.GetAllTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));

  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::GetTasksForToday() {
  auto tasks = task_view_.GetTodayTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::GetTasksForWeek() {
  auto tasks = task_view_.GetWeekTasks();
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::GetTasksForName(const std::string &name) {
  auto tasks = task_view_.GetTasksByName(name);
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::vector<TaskDTO> TaskServiceStorage::GetTasksForLabel(const std::string &label) {
  auto tasks = task_view_.GetTasksByLabel(label);
  std::vector<TaskDTO> searchResult;
  for(auto task : tasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

std::optional<TaskDTO> TaskServiceStorage::GetTaskById(const TaskID &id) {
  auto task = task_storage_.GetTask(id);
  if(task.has_value()) {
    return TaskDTO::create(task.value()->GetID(), task.value()->GetTask(), task.value()->GetStatus());
  }
  return std::nullopt;
}

OperationResult TaskServiceStorage::AddTask(const Task &task) {
  auto newid = generate_id_.GenerateID();
  auto newtask = TaskEntity::create(task, newid);
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  task_storage_.PushTask(std::make_pair(newid, task_ptr));
  task_view_.AddTask(task_ptr);

  if(newid.GetID() > 9999) return OperationResult::create(ErrorCode::MEMORY_LIMIT);
  return OperationResult::create(ErrorCode::NO_ERRORS);
}

OperationResult TaskServiceStorage::AddSubtask(const TaskID &id, const Task &subtask) {
  auto task = task_storage_.GetTask(id);
  if(!task.has_value()) return OperationResult::create(ErrorCode::PARENT_NOT_FOUND);

  auto newid = generate_id_.GenerateID();
  auto newtask = TaskEntity::create(subtask, newid);
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  task_storage_.PushTask(std::make_pair(newid, task_ptr));
  task_view_.AddTask(task_ptr);
  task.value()->AddSubtask(task_ptr);

  if(newid.GetID() > 9999) return OperationResult::create(ErrorCode::MEMORY_LIMIT);
  return OperationResult::create(ErrorCode::NO_ERRORS);
}