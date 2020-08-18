//
// Created by rodion on 7/15/20.
//

#include "TaskService.h"

TaskService::TaskService() : task_service_storage_(FullStorage()) {}

std::vector<TaskDTO> TaskService::getAllTasks(const bool& sortByPriority) const {
  std::vector<TaskDTO> searchResult;
  auto allTasks = task_service_storage_.GetTaskView().GetAllTasks();
  for (const auto &task : allTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForToday(const bool& sortByPriority) const {
  auto todayTasks = task_service_storage_.GetTaskView().GetTodayTasks();
  std::vector<TaskDTO> searchResult;
  for(const auto& task : todayTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(const bool& sortByPriority) const {
  auto weekTasks = task_service_storage_.GetTaskView().GetWeekTasks();
  std::vector<TaskDTO> searchResult;
  for(const auto& task : weekTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByLabel(const std::string &label, const bool& sortByPriority) const {
  auto labelTasks = task_service_storage_.GetTaskView().GetTasksByLabel(label);
  std::vector<TaskDTO> searchResult;
  for(const auto& task : labelTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByName(const std::string &name, const bool& sortByPriority) const {
  auto nameTasks = task_service_storage_.GetTaskView().GetTasksByName(name);
  std::vector<TaskDTO> searchResult;
  for(const auto& task : nameTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  if(sortByPriority) return sortedByPriority(searchResult);
  return searchResult;
}

std::vector<TaskDTO> TaskService::getTasksByPriority(const Priority &priority) const {
  auto priorityTasks = task_service_storage_.GetTaskView().GetTasksByPriority(priority);
  std::vector<TaskDTO> searchResult;
  for(const auto& task : priorityTasks) {
    searchResult.push_back(TaskDTO::create(task.GetID(), task.GetTask(), task.GetStatus()));
  }
  return searchResult;
}

OperationResult TaskService::addTask(const TaskDTO &task) {
  return task_service_storage_.AddTask(task);
}

OperationResult TaskService::addSubtask(const TaskID &id, const TaskDTO& subtask) {
  return task_service_storage_.AddSubtask(id, subtask);
}

OperationResult TaskService::RemoveTask(const TaskID &id) {
  return task_service_storage_.RemoveTask(id);
}

OperationResult TaskService::postponeTask(const TaskID &id, const Date &newdate) {
  auto task = task_service_storage_.GetTaskStorage().GetTask(id);
  if(task == nullptr) return OperationResult{ErrorCode::TASK_NOT_FOUND};

  auto newtask = Task::create(task->GetName(), task->GetLabel(), task->GetPriority(), newdate);
  if(!newtask.has_value()) return OperationResult{ErrorCode::INVALID_DATE};
  task->SubstituteTask(newtask.value());

  return OperationResult{ErrorCode::NO_ERRORS};
}

OperationResult TaskService::completeTask(const TaskID &id) {
  auto task = task_service_storage_.GetTaskStorage().GetTask(id);
  if(task == nullptr) return OperationResult{ErrorCode::TASK_NOT_FOUND};

  if(!task->SetComplete()) return OperationResult{ErrorCode::COMPLETED_TASK};

  return OperationResult{ErrorCode::NO_ERRORS};
}

std::vector<TaskDTO> TaskService::sortedByPriority(std::vector<TaskDTO> vector) {
  sort(vector.begin(), vector.end(),
              [](const TaskDTO& lhs, const TaskDTO& rhs) { return lhs.getPriority() < rhs.getPriority(); });
  return vector;
}
