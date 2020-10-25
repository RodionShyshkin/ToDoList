//
// Created by rodion on 7/15/20.
//

#include <Persister/FilePersister.h>
#include "TaskService.h"
#include <future>

TaskService::TaskService() : model_api_(std::make_unique<TaskModel>()) { }

TaskService::TaskService(std::unique_ptr<TaskModelInterface> model) : model_api_(std::move(model)) {}

std::optional<TaskDTO> TaskService::getTask(const unsigned int& id) const {
  auto result = model_api_->getTask(TaskID{id});
  if(!result.has_value()) return std::nullopt;

  return TaskService::convertFromModelDTO(result.value());
}

std::vector<TaskDTO> TaskService::getAllTasks(const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto allTasks = model_api_->getAllTasks();
  for(const auto& model_dto : allTasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->getTasksForToday();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->getTasksForWeek();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByLabel(const std::string &label, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->getTasksByLabel(label);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByName(const std::string &name, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->getTasksByName(name);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByPriority(const Priority& priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = model_api_->getTasksByPriority(priority);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskService::convertFromModelDTO(model_dto));
  }
  return searchResult;
}

OperationResult<StorageError> TaskService::addTask(const TaskDTO &task) {
  return model_api_->AddTask(TaskService::convertToModelDTO(task));
}

OperationResult<StorageError> TaskService::addSubtask(const unsigned int& id, const TaskDTO& subtask) {
  return model_api_->AddSubtask(TaskID{id}, TaskService::convertToModelDTO(subtask));
}

OperationResult<StorageError> TaskService::RemoveTask(const unsigned int& id) {
  return model_api_->RemoveTask(TaskID{id});
}

bool TaskService::postponeTask(const unsigned int& id, const boost::gregorian::date& newdate) {
  return model_api_->postponeTask(TaskID{id}, Date{newdate});
}

bool TaskService::completeTask(const unsigned int& id) {
  return model_api_->completeTask(TaskID{id});
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
 return ModelTaskDTO::createWithoutParent(TaskID{dto.getID()}, dto.getName(), dto.getLabel(),
                             dto.getPriority(), Date{dto.getDueDate()}, dto.getStatus());
}