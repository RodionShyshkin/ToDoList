//
// Created by rodion on 8/10/20.
//

#include "TaskModel.h"
#include <src/core/Persister/Serialization/StorageToProtoConverter.h>
#include <src/core/Persister/Serialization/ProtoToStorageConverter.h>
#include <Persister/Persister.h>
#include <fstream>
#include "task.pb.h"

TaskModel::TaskModel() : generate_id_(std::make_unique<IDGenerator>()),
                         task_storage_(std::make_unique<TaskStorage>()),
                          task_view_(std::make_unique<TaskView>()) {}

TaskModel::TaskModel(std::unique_ptr<TaskStorageInterface> storage,
                     std::unique_ptr<TaskViewInterface> view,
                     std::unique_ptr<IDGeneratorInterface> generator) {
  this->task_storage_ = std::move(storage);
  this->task_view_ = std::move(view);
  this->generate_id_ = std::move(generator);
}

TaskViewInterface& TaskModel::GetTaskView() const {
  return *this->task_view_;
}

TaskStorageInterface& TaskModel::GetTaskStorage() const {
  return *this->task_storage_;
}

OperationResult<StorageError> TaskModel::AddTask(const ModelTaskDTO& task) {
  auto taskInstance = Task::create(task.getName(), task.getLabel(), task.getPriority(), task.getDueDate());
  if(!taskInstance.has_value()) return OperationResult{StorageError::INVALID_TASK};

  auto newid = generate_id_->GenerateID();
  if(!newid.has_value()) return OperationResult{StorageError::MEMORY_LIMIT};

  auto newtask = TaskEntity::createTask(taskInstance.value(), newid.value());
  if(task.getStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!this->task_storage_->AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  if(!this->task_view_->AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<StorageError> TaskModel::AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) {
  auto taskInstance = Task::create(subtask.getName(), subtask.getLabel(), subtask.getPriority(), subtask.getDueDate());
  if(!taskInstance.has_value()) return OperationResult{StorageError::INVALID_TASK};

  auto task = this->task_storage_->GetTask(id);
  if(task == nullptr) return OperationResult{StorageError::PARENT_NOT_FOUND};

  auto newid = generate_id_->GenerateID();
  if(!newid.has_value()) return OperationResult{StorageError::MEMORY_LIMIT};
  auto newtask = TaskEntity::createSubtask(taskInstance.value(), newid.value(), id);
  if(subtask.getStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_->AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  if(!task_view_->AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  task->AddSubtask(task_ptr);

  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<StorageError> TaskModel::RemoveTask(const TaskID &id) {
  auto task = task_storage_->GetTask(id);
  if(task == nullptr) return OperationResult{StorageError::TASK_NOT_FOUND};
  std::vector<TaskID> subtasksToRemove;

  auto subtasks = task->GetSubtasks();
  for(const auto& subtask : subtasks) {
    subtasksToRemove.push_back(subtask.first);
    RemoveTask(subtask.first);
  }

  for(const auto& subtask : subtasksToRemove) {
    if(!task_storage_->RemoveTask(subtask)) return OperationResult{StorageError::WRONG_TASK_ID};
    if(!task_view_->RemoveTask(subtask)) return OperationResult{StorageError::WRONG_TASK_ID};
  }

  if(task->checkParent()) {
    auto parentID = task->GetParentID();
    if(task_storage_->GetTask(parentID) == nullptr) throw std::runtime_error("Parent was lost.");
    auto parent = task_storage_->GetTask(parentID);
    if(!parent->RemoveSubtask(id)) throw std::runtime_error("Subtask was lost.");
  }

  task_storage_->RemoveTask(id);
  task_view_->RemoveTask(id);

  return OperationResult{StorageError::NO_ERRORS};
}

std::vector<ModelTaskDTO> TaskModel::GetSubtasks(const TaskID &id) {
  auto task = this->task_storage_->GetTask(id);
  auto subtasks = task->GetSubtasks();

  std::vector<ModelTaskDTO> result;
  for(const auto& subtask : subtasks) {
    result.push_back(ModelTaskDTO::createWithParent(subtask.second.lock()->GetID(),
                                                    subtask.second.lock()->GetName(),
                                                    subtask.second.lock()->GetLabel(),
                                                    subtask.second.lock()->GetPriority(),
                                                    subtask.second.lock()->GetDueTime(),
                                                    subtask.second.lock()->GetStatus(),
                                                    subtask.second.lock()->GetParentID()));
  }
  return result;
}

std::unique_ptr<TaskModel> TaskModel::createByTasks(const std::vector<ModelTaskDTO> &tasks) {
  auto temp_model = std::make_unique<TaskModel>();
  for(const auto& task : tasks) {
    if(task.getParentID() == task.getID()) {
      temp_model->AddTask(task);
    }
    else temp_model->AddSubtask(task.getParentID(), task);
  }
  return temp_model;
}
