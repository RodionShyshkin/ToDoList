//
// Created by rodion on 9/29/20.
//

#include <src/core/Persister/Persister.h>
#include "ModelAPI.h"

ModelAPI::ModelAPI() : model_(std::make_unique<TaskModel>()) { }

ModelTaskDTO ModelAPI::getTask(const TaskID &id) const {
  auto task = this->model_->GetTaskStorage().GetTask(id);

  return ModelTaskDTO::createWithoutParent(task->GetID(), task->GetName(), task->GetLabel(),
                              task->GetPriority(), task->GetDueTime(), task->GetStatus());
}

std::vector<ModelTaskDTO> ModelAPI::getAllTasks() const {
  auto tasks = this->model_->GetTaskView().GetAllTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

std::vector<ModelTaskDTO> ModelAPI::getTasksForToday() const {
  auto tasks = this->model_->GetTaskView().GetTodayTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

std::vector<ModelTaskDTO> ModelAPI::getTasksForWeek() const {
  auto tasks = this->model_->GetTaskView().GetWeekTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

std::vector<ModelTaskDTO> ModelAPI::getTasksByLabel(const std::string& label) const {
  auto tasks = this->model_->GetTaskView().GetTasksByLabel(label);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

std::vector<ModelTaskDTO> ModelAPI::getTasksByName(const std::string& name) const {
  auto tasks = this->model_->GetTaskView().GetTasksByName(name);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

std::vector<ModelTaskDTO> ModelAPI::getTasksByPriority(const Priority& priority) const {
  auto tasks = this->model_->GetTaskView().GetTasksByPriority(priority);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(ModelTaskDTO::createWithoutParent(task.GetID(), task.GetName(), task.GetLabel(),
                                          task.GetPriority(), task.GetDueTime(), task.GetStatus()));
  }
  return result;
}

OperationResult<StorageError> ModelAPI::addTask(const ModelTaskDTO &task) {
  return this->model_->AddTask(task);
}

OperationResult<StorageError> ModelAPI::addSubtask(const TaskID &id, const ModelTaskDTO &subtask) {
  return this->model_->AddSubtask(id, subtask);
}

OperationResult<StorageError> ModelAPI::RemoveTask(const TaskID &id) {
  return this->model_->RemoveTask(id);
}

OperationResult<StorageError> ModelAPI::postponeTask(const TaskID &id, const Date &newdate) {
  auto task = this->model_->GetTaskStorage().GetTask(id);
  if(task == nullptr) return OperationResult<StorageError>{StorageError::TASK_NOT_FOUND};

  auto newtask = Task::create(task->GetName(), task->GetLabel(), task->GetPriority(), newdate);
  if(!newtask.has_value()) return OperationResult{StorageError::INVALID_DATE};
  task->SubstituteTask(newtask.value());

  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<StorageError> ModelAPI::completeTask(const TaskID &id) {
  auto task = this->model_->GetTaskStorage().GetTask(id);
  if(task == nullptr) return OperationResult{StorageError::TASK_NOT_FOUND};

  if(!task->SetComplete()) return OperationResult{StorageError::COMPLETED_TASK};

  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<SerializationError> ModelAPI::saveToDisk(const std::string &path) {
  auto tasks = this->getAllTasks();
  Persister persister{path, tasks};
  if(!persister.Save()) return OperationResult{SerializationError::SERIALIZATION_ERROR};

  return OperationResult{SerializationError::NO_ERRORS};
}

OperationResult<SerializationError> ModelAPI::loadFromDisk(const std::string &path) {
  std::vector<ModelTaskDTO> tasks;
  Persister persister{path, tasks};
  if(!persister.Load()) return OperationResult{SerializationError::DESERIALIZATION_ERROR};

  auto model = TaskModel::createByTasks(tasks);
  std::swap(model_, model);

  return OperationResult{SerializationError::NO_ERRORS};
}

