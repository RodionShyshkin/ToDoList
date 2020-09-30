//
// Created by rodion on 8/10/20.
//

#include "TaskModel.h"
#include <src/core/Persister/Serialization/StorageToProtoConverter.h>
#include <src/core/Persister/Serialization/ProtoToStorageConverter.h>
#include <Persister/Persister.h>
#include <fstream>
#include "task.pb.h"

TaskModel::TaskModel() : generate_id_(IDGenerator()), task_view_(TaskView()), task_storage_(TaskStorage()) {}

TaskView TaskModel::GetTaskView() const {
  return task_view_;
}

TaskStorage TaskModel::GetTaskStorage() const {
  return task_storage_;
}

IDGenerator TaskModel::GetIDGenerator() const {
  return this->generate_id_;
}

OperationResult<StorageError> TaskModel::AddTask(const ModelTaskDTO& task) {
  auto taskInstance = Task::create(task.getName(), task.getLabel(), task.getPriority(), task.getDueDate());
  if(!taskInstance.has_value()) return OperationResult{StorageError::INVALID_TASK};

  auto newid = generate_id_.GenerateID();
  if(!newid.has_value()) return OperationResult{StorageError::MEMORY_LIMIT};

  auto newtask = TaskEntity::createTask(taskInstance.value(), newid.value());
  if(task.getStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_.AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  if(!task_view_.AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<StorageError> TaskModel::AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) {
  auto taskInstance = Task::create(subtask.getName(), subtask.getLabel(), subtask.getPriority(), subtask.getDueDate());
  if(!taskInstance.has_value()) return OperationResult{StorageError::INVALID_TASK};

  auto task = task_storage_.GetTask(id);
  if(task == nullptr) return OperationResult{StorageError::PARENT_NOT_FOUND};

  auto newid = generate_id_.GenerateID();
  if(!newid.has_value()) return OperationResult{StorageError::MEMORY_LIMIT};
  auto newtask = TaskEntity::createSubtask(taskInstance.value(), newid.value(), id);
  if(subtask.getStatus()) newtask.SetComplete();
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_.AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  if(!task_view_.AddTask(task_ptr)) return OperationResult{StorageError::WRONG_TASK_ID};
  task->AddSubtask(task_ptr);

  return OperationResult{StorageError::NO_ERRORS};
}

OperationResult<StorageError> TaskModel::RemoveTask(const TaskID &id) {
  auto task = task_storage_.GetTask(id);
  if(task == nullptr) return OperationResult{StorageError::TASK_NOT_FOUND};
  std::vector<TaskID> subtasksToRemove;

  auto subtasks = task->GetSubtasks();
  for(const auto& subtask : subtasks) {
    subtasksToRemove.push_back(subtask.first);
    RemoveTask(subtask.first);
  }

  for(const auto& subtask : subtasksToRemove) {
    if(!task_storage_.RemoveTask(subtask)) return OperationResult{StorageError::WRONG_TASK_ID};
    if(!task_view_.RemoveTask(subtask)) return OperationResult{StorageError::WRONG_TASK_ID};
  }

  if(task->checkParent()) {
    auto parentID = task->GetParentID();
    if(task_storage_.GetTask(parentID) == nullptr) throw std::runtime_error("Parent was lost.");
    auto parent = task_storage_.GetTask(parentID);
    if(!parent->RemoveSubtask(id)) throw std::runtime_error("Subtask was lost.");
  }

  task_storage_.RemoveTask(id);
  task_view_.RemoveTask(id);

  return OperationResult{StorageError::NO_ERRORS};
}
/*
OperationResult<SerializationError> TaskModel::SaveToDisk(const std::string &path) const {
  auto tasks = this->GetTaskView().GetAllTasks();
  StorageProto storage = StorageToProtoConverter::ConvertStorageToProto(tasks);
  Persister persister{path, storage};
  if(!persister.Save()) return OperationResult{SerializationError::SERIALIZATION_ERROR};

  return OperationResult{SerializationError::NO_ERRORS};
}

OperationResult<SerializationError> TaskModel::LoadFromDisk(const std::string &path) const {
  StorageProto storage;
  Persister persister{path, storage};
  if(!persister.Load()) return OperationResult{SerializationError::DESERIALIZATION_ERROR};

  TaskModel temp_model;
  auto tasks = ProtoToStorageConverter::Convert(storage);
  for(const auto& task : tasks) {
    if(task.getParentID() == task.getID()) {
      temp_model.AddTask(task);
    }
    else temp_model.AddSubtask(task.getParentID(), task);
  }

  return OperationResult{SerializationError::NO_ERRORS};
}
*/

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

