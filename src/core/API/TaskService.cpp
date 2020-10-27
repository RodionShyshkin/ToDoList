//
// Created by rodion on 7/15/20.
//

#include <Persister/FilePersister.h>
#include "TaskService.h"
#include <future>

TaskService::TaskService() : model_api_(std::make_unique<TaskModel>()) { }

TaskService::TaskService(std::unique_ptr<TaskModelInterface> model) : model_api_(std::move(model)) {}

std::optional<TaskDTO> TaskService::GetTask(const unsigned int& id) const {
  auto result = model_api_->GetTask(TaskID{id});
  if(!result.has_value()) return std::nullopt;

  return api_converter::ConvertFromModelDTO(result.value());
}

std::vector<TaskDTO> TaskService::GetAllTasks(const bool& sort_by_priority) const {
  std::vector<TaskDTO> searchResult;
  auto allTasks = model_api_->GetAllTasks();
  for(const auto& model_dto : allTasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  if(sort_by_priority) return api_converter::GetSortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::GetTasksForToday(const bool &sort_by_priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->GetTasksForToday();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  if(sort_by_priority) return api_converter::GetSortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::GetTasksForWeek(const bool &sort_by_priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->GetTasksForWeek();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  if(sort_by_priority) return api_converter::GetSortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::GetTasksByLabel(const std::string &label, const bool& sort_by_priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->GetTasksByLabel(label);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  if(sort_by_priority) return api_converter::GetSortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::GetTasksByName(const std::string &name, const bool& sort_by_priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->GetTasksByName(name);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  if(sort_by_priority) return api_converter::GetSortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::GetTasksByPriority(const Priority& priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->GetTasksByPriority(priority);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(api_converter::ConvertFromModelDTO(model_dto));
  }
  return searchResult;
}

OperationResult<StorageError> TaskService::AddTask(const TaskDTO &task) {
  return model_api_->AddTask(api_converter::ConvertToModelDTO(task));
}

OperationResult<StorageError> TaskService::AddSubtask(const unsigned int& id, const TaskDTO& subtask) {
  return model_api_->AddSubtask(TaskID{id}, api_converter::ConvertToModelDTO(subtask));
}

OperationResult<StorageError> TaskService::RemoveTask(const unsigned int& id) {
  return model_api_->RemoveTask(TaskID{id});
}

bool TaskService::PostponeTask(const unsigned int& id, const boost::gregorian::date& new_date) {
  return model_api_->PostponeTask(TaskID{id}, Date{new_date});
}

bool TaskService::CompleteTask(const unsigned int& id) {
  return model_api_->CompleteTask(TaskID{id});
}

OperationResult<PersistError> TaskService::Save(const std::string &filepath) {
  std::fstream file(filepath, std::ios::out);
  auto persister = std::make_unique<FilePersister>(std::move(file), *model_api_);
  auto future = std::async(std::bind(&PersisterInterface::Save, persister.get()));
  future.wait();
  if(!future.get()) return OperationResult<PersistError>::Fail(PersistError::SAVE_ERROR);

  return OperationResult<PersistError>::Success();
}

OperationResult<PersistError> TaskService::Load(const std::string &filepath) {
  std::fstream file(filepath, std::ios::in);
  std::unique_ptr<TaskModelInterface> newmodel = std::make_unique<TaskModel>();
  auto persister = std::make_unique<FilePersister>(std::move(file), *newmodel);
  auto future = std::async(std::bind(&PersisterInterface::Load, persister.get()));
  if(!future.get()) return OperationResult<PersistError>::Fail(PersistError::LOAD_ERROR);
  std::swap(model_api_, newmodel);

  return OperationResult<PersistError>::Success();
}
