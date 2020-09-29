//
// Created by rodion on 7/15/20.
//

#include "TaskService.h"

TaskService::TaskService() : memory_model_api_(std::make_unique<ModelAPI>()) { }

TaskDTO TaskService::getTask(const unsigned int& id) const {
  auto model_dto = memory_model_api_->getTask(TaskID{id});

  return TaskService::convertFromModelDTO(model_dto);
}

std::vector<TaskDTO> TaskService::getAllTasks(const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto allTasks = memory_model_api_->getAllTasks();
  for(const auto& model_dto : allTasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksForToday();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksForWeek();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByLabel(const std::string &label, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByLabel(label);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByName(const std::string &name, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByName(name);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByPriority(const Priority& priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByPriority(priority);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  return searchResult;
}

OperationResult<StorageError> TaskService::addTask(const TaskDTO &task) {
  return memory_model_api_->addTask(TaskService::convertToModelDTO(task));
}

OperationResult<StorageError> TaskService::addSubtask(const unsigned int& id, const TaskDTO& subtask) {
  return memory_model_api_->addSubtask(TaskID{id}, TaskService::convertToModelDTO(subtask));
}

OperationResult<StorageError> TaskService::RemoveTask(const unsigned int& id) {
  return memory_model_api_->RemoveTask(TaskID{id});
}

OperationResult<StorageError> TaskService::postponeTask(const unsigned int& id, const boost::gregorian::date& newdate) {
  return memory_model_api_->postponeTask(TaskID{id}, Date{newdate});
}

OperationResult<StorageError> TaskService::completeTask(const unsigned int& id) {
  return memory_model_api_->completeTask(TaskID{id});
}

std::vector<TaskDTO> TaskService::sortedByPriority(std::vector<TaskDTO> vector) {
  sort(vector.begin(), vector.end(),
              [](const TaskDTO& lhs, const TaskDTO& rhs) { return lhs.getPriority() < rhs.getPriority(); });
  return vector;
}

TaskDTO TaskService::convertFromModelDTO(const ModelTaskDTO &model_dto) {
  return TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(), model_dto.getLabel(),
                         model_dto.getPriority(), model_dto.getDueDate().GetDate(), model_dto.getStatus());
}

ModelTaskDTO TaskService::convertToModelDTO(const TaskDTO &dto) {
 return ModelTaskDTO::create(TaskID{dto.getID()}, dto.getName(), dto.getLabel(),
                             dto.getPriority(), Date{dto.getDueDate()}, dto.getStatus());
}