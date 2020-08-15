//
// Created by rodion on 8/10/20.
//

#include "FullStorage.h"

FullStorage::FullStorage() : generate_id_(IDGenerator()) {}

TaskView FullStorage::GetTaskView() const {
  return task_view_;
}

TaskStorage FullStorage::GetTaskStorage() const {
  return task_storage_;
}

OperationResult FullStorage::AddTask(const Task &task) {
  auto newid = generate_id_.GenerateID();
  if(!newid.has_value()) return OperationResult{ErrorCode::MEMORY_LIMIT};
  auto newtask = TaskEntity::createTask(task, newid.value());
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_.AddTask(task_ptr)) return OperationResult{ErrorCode::WRONG_TASK_ID};
  if(!task_view_.AddTask(task_ptr)) return OperationResult{ErrorCode::WRONG_TASK_ID};

  return OperationResult{ErrorCode::NO_ERRORS};
}

OperationResult FullStorage::AddSubtask(const TaskID &id, const Task &subtask) {
  auto task = task_storage_.GetTask(id);
  if(task == nullptr) return OperationResult{ErrorCode::PARENT_NOT_FOUND};

  auto newid = generate_id_.GenerateID();
  if(!newid.has_value()) return OperationResult{ErrorCode::MEMORY_LIMIT};
  auto newtask = TaskEntity::createSubtask(subtask, newid.value(), id);
  auto task_ptr = std::make_shared<TaskEntity>(newtask);

  if(!task_storage_.AddTask(task_ptr)) return OperationResult{ErrorCode::WRONG_TASK_ID};
  if(!task_view_.AddTask(task_ptr)) return OperationResult{ErrorCode::WRONG_TASK_ID};
  task->AddSubtask(task_ptr);

  return OperationResult{ErrorCode::NO_ERRORS};
}

OperationResult FullStorage::RemoveTask(const TaskID &id) {
  auto task = task_storage_.GetTask(id);
  if(task == nullptr) return OperationResult{ErrorCode::TASK_NOT_FOUND};
  std::vector<TaskID> subtasksToRemove;

  auto subtasks = task->GetSubtasks();
  for(const auto& subtask : subtasks) {
    subtasksToRemove.push_back(subtask.first);
    RemoveTask(subtask.first);
  }

  for(const auto& subtask : subtasksToRemove) {
    if(!task_storage_.RemoveTask(subtask)) return OperationResult{ErrorCode::WRONG_TASK_ID};
    if(!task_view_.RemoveTask(subtask)) return OperationResult{ErrorCode::WRONG_TASK_ID};
  }

  if(task->checkParent()) {
    auto parentID = task->GetParentID();
    if(!task_storage_.HasTask(parentID)) throw std::runtime_error("Parent was lost.");
    auto parent = task_storage_.GetTask(parentID);
    if(!parent->RemoveSubtask(id)) throw std::runtime_error("Subtask was lost.");
  }

  task_storage_.RemoveTask(id);
  task_view_.RemoveTask(id);

  return OperationResult{ErrorCode::NO_ERRORS};
}