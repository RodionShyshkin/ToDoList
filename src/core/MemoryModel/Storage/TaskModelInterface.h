//
// Created by rodion on 8/17/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
#define TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_

#include <MemoryModel/Storage/TaskView.h>
#include <MemoryModel/Storage/TaskStorage.h>
#include <src/core/API/OperationResult.h>
#include <src/core/MemoryModel/MemoryModelAPI/ModelTaskDTO.h>
#include <src/core/Persister/SerializationError.h>

class TaskModelInterface {
 public:
  virtual ~TaskModelInterface() = default;

 public:
  virtual TaskViewInterface&          GetTaskView() const = 0;
  virtual TaskStorageInterface&       GetTaskStorage() const = 0;

  virtual OperationResult<StorageError>                   AddTask(const ModelTaskDTO& task) = 0;
  virtual OperationResult<StorageError>                   AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) = 0;
  virtual OperationResult<StorageError>                   RemoveTask(const TaskID& id) = 0;

  virtual std::vector<ModelTaskDTO>                       GetSubtasks(const TaskID& id) = 0;
};

#endif //TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
