//
// Created by rodion on 7/15/20.
//

#include "TaskService.h"

TaskService::TaskService() = default;

TaskDTO TaskService::getTask(const TaskID &id) const {
  auto model_dto = memory_model_api_->getTask(id);

  return TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                         model_dto.getLabel(), model_dto.getPriority(),
                         model_dto.getDueDate().GetDate(), model_dto.getStatus());
}

std::vector<TaskDTO> TaskService::getAllTasks(const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto allTasks = memory_model_api_->getAllTasks();
  for(const auto& model_dto : allTasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksForToday();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(const bool &sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksForWeek();
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByLabel(const std::string &label, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByLabel(label);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByName(const std::string &name, const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByName(name);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByPriority(const Priority& priority) const {
  std::vector<TaskDTO> searchResult;
  auto tasks = memory_model_api_->getTasksByPriority(priority);
  for(const auto& model_dto : tasks) {
    searchResult.push_back(TaskDTO::create(model_dto.getID().GetID(), model_dto.getName(),
                                           model_dto.getLabel(), model_dto.getPriority(),
                                           model_dto.getDueDate().GetDate(), model_dto.getStatus()));
  }
  return searchResult;
}

OperationResult TaskService::addTask(const TaskDTO &task) {
  auto model_dto = ModelTaskDTO::create(TaskID{task.getID()}, task.getName(), task.getLabel(),
                                        task.getPriority(), Date{task.getDueDate()}, task.getStatus());
  return memory_model_api_->addTask(model_dto);
}

OperationResult TaskService::addSubtask(const TaskID &id, const TaskDTO& subtask) {
  auto model_dto = ModelTaskDTO::create(TaskID{subtask.getID()}, subtask.getName(), subtask.getLabel(),
                                        subtask.getPriority(), Date{subtask.getDueDate()}, subtask.getStatus());
  return memory_model_api_->addSubtask(id, model_dto);
}

OperationResult TaskService::RemoveTask(const TaskID &id) {
  return memory_model_api_->RemoveTask(id);
}

OperationResult TaskService::postponeTask(const TaskID &id, const Date &newdate) {
  return memory_model_api_->postponeTask(id, newdate);
}

OperationResult TaskService::completeTask(const TaskID &id) {
  return memory_model_api_->completeTask(id);
}

std::vector<TaskDTO> TaskService::sortedByPriority(std::vector<TaskDTO> vector) {
  sort(vector.begin(), vector.end(),
              [](const TaskDTO& lhs, const TaskDTO& rhs) { return lhs.getPriority() < rhs.getPriority(); });
  return vector;
}
