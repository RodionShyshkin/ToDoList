//
// Created by rodion on 8/10/20.
//

#include "TaskModel.h"
#include <Persister/FilePersister.h>
#include <fstream>
#include "task.pb.h"
#include "ModelTaskDTOConverter.h"

TaskModel::TaskModel() : generate_id_(std::make_unique<IDGenerator>()),
                         task_storage_(std::make_unique<TaskStorage>()),
                          task_view_(std::make_unique<TaskView>()) {}

TaskModel::TaskModel(std::unique_ptr<TaskStorageInterface> storage,
                            std::unique_ptr<TaskViewInterface> view,
                      std::unique_ptr<IDGeneratorInterface> generator) :
                        task_storage_(std::move(storage)), task_view_(std::move(view)),
                        generate_id_(std::move(generator)) { }

std::optional<ModelTaskDTO> TaskModel::GetTask(const TaskID &id) const {
  auto task = task_storage_->GetTask(id);
  if(task == nullptr) return std::nullopt;
  return model_task_dto_converter::Convert(*task);
}

std::vector<ModelTaskDTO> TaskModel::GetAllTasks() const {
  auto tasks =  task_storage_->GetAllTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

std::vector<ModelTaskDTO> TaskModel::GetTasksForToday() const {
  auto tasks =  task_view_->GetTodayTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

std::vector<ModelTaskDTO> TaskModel::GetTasksForWeek() const {
  auto tasks =  task_view_->GetWeekTasks();
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {

    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

std::vector<ModelTaskDTO> TaskModel::GetTasksByLabel(const std::string &label) const {
  auto tasks =  task_view_->GetTasksByLabel(label);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

std::vector<ModelTaskDTO> TaskModel::GetTasksByName(const std::string &name) const {
  auto tasks =  task_view_->GetTasksByName(name);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

std::vector<ModelTaskDTO> TaskModel::GetTasksByPriority(const Priority &priority) const {
  auto tasks =  task_view_->GetTasksByPriority(priority);
  std::vector<ModelTaskDTO> result;
  for(const auto& task : tasks) {
    result.push_back(model_task_dto_converter::Convert(task));
  }
  return result;
}

OperationResult<StorageError> TaskModel::AddTask(const ModelTaskDTO& task) {
  auto taskInstance = Task::create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDueDate());
  if(!taskInstance.has_value()) return OperationResult<StorageError>::Fail(StorageError::INVALID_TASK);

  auto newid = generate_id_->GenerateID();
  auto newtask = TaskEntity::createTask(taskInstance.value(), newid);
  if(task.GetStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_->AddTask(task_ptr)) return OperationResult<StorageError>::Fail(StorageError::WRONG_TASK_ID);
  if(!task_view_->AddTask(task_ptr)) return OperationResult<StorageError>::Fail(StorageError::WRONG_TASK_ID);

  return OperationResult<StorageError>::Success();
}

OperationResult<StorageError> TaskModel::AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) {
  auto taskInstance = Task::create(subtask.GetName(), subtask.GetLabel(), subtask.GetPriority(), subtask.GetDueDate());
  if(!taskInstance.has_value()) return OperationResult<StorageError>::Fail(StorageError::INVALID_TASK);

  auto task =  task_storage_->GetTask(id);
  if(task == nullptr) return OperationResult<StorageError>::Fail(StorageError::PARENT_NOT_FOUND);

  auto newid = generate_id_->GenerateID();
  auto newtask = TaskEntity::createSubtask(taskInstance.value(), newid, id);
  if(subtask.GetStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(! task_storage_->AddTask(task_ptr)) return OperationResult<StorageError>::Fail(StorageError::WRONG_TASK_ID);
  if(! task_view_->AddTask(task_ptr)) return OperationResult<StorageError>::Fail(StorageError::WRONG_TASK_ID);
  task->AddSubtask(task_ptr);

  return OperationResult<StorageError>::Success();
}

OperationResult<StorageError> TaskModel::RemoveTask(const TaskID &id) {
  auto task = task_storage_->GetTask(id);
  if(task == nullptr) return OperationResult<StorageError>::Fail(StorageError::TASK_NOT_FOUND);
  std::vector<TaskID> subtasksToRemove;

  auto subtasks = task->GetSubtasks();
  for(const auto& subtask : subtasks) {
    subtasksToRemove.push_back(subtask.first);
    RemoveTask(subtask.first);
  }

  if(task->checkParent()) {
    auto parentID = task->GetParentID();
    auto parent = task_storage_->GetTask(parentID);
    if(!parent->RemoveSubtask(id)) throw std::runtime_error("Subtask was lost.");
  }

  task_storage_->RemoveTask(id);
  task_view_->RemoveTask(id);

  return OperationResult<StorageError>::Success();
}

std::vector<ModelTaskDTO> TaskModel::GetSubtasks(const TaskID &id) {
  auto task = task_storage_->GetTask(id);
  auto subtasks = task->GetSubtasks();

  std::vector<ModelTaskDTO> result;
  for(const auto& subtask : subtasks) {
    auto model_dto = model_task_dto_converter::Convert(*subtask.second.lock());
    result.push_back(model_dto);
  }

  return result;
}

bool TaskModel::CompleteTask(const TaskID &id) {
  auto task =  task_storage_->GetTask(id);
  if(task == nullptr) return false;
  std::vector<TaskID> subtasksToComplete;

  auto subtasks = task->GetSubtasks();
  for(const auto& subtask : subtasks) {
    subtasksToComplete.push_back(subtask.first);
    CompleteTask(subtask.first);
  }

  task->SetComplete();
  return true;
}

bool TaskModel::PostponeTask(const TaskID &id, const Date &newdate) {
  auto task =  task_storage_->GetTask(id);
  if(task == nullptr) return false;

  auto newtask = Task::create(task->GetName(), task->GetLabel(), task->GetPriority(), newdate);
  if(!newtask.has_value()) return false;
  task->SubstituteTask(newtask.value());
  return true;
}
