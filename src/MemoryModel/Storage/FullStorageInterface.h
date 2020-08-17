//
// Created by rodion on 8/17/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
#define TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_

#include <MemoryModel/Storage/TaskView.h>
#include <MemoryModel/Storage/TaskStorage.h>
#include <MemoryModel/Storage/OperationResult.h>
#include <API/TaskDTO.h>

class FullStorageInterface {
 public:
  virtual ~FullStorageInterface() = default;

 public:
  virtual TaskView                          GetTaskView() const = 0;
  virtual TaskStorage                       GetTaskStorage() const = 0;

  virtual OperationResult                   AddTask(const TaskDTO& task) = 0;
  virtual OperationResult                   AddSubtask(const TaskID &id, const TaskDTO& subtask) = 0;
  virtual OperationResult                   RemoveTask(const TaskID& id) = 0;
};

#endif //TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
