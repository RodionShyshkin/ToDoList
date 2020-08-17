//
// Created by rodion on 8/17/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKSTORAGEINTERFACE_H_
#define TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKSTORAGEINTERFACE_H_

#include <memory>
#include <MemoryModel/Task/TaskEntity.h>

class TaskStorageInterface {
 public:
  virtual ~TaskStorageInterface() = default;

 public:
  virtual bool                                    AddTask(const std::shared_ptr<TaskEntity>& task) = 0;
  virtual bool                                    RemoveTask(const TaskID& id) = 0;

  virtual bool                                    HasTask(const TaskID& id) = 0;
  virtual std::shared_ptr<TaskEntity>             GetTask(const TaskID& id) = 0;
};

#endif //TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKSTORAGEINTERFACE_H_
