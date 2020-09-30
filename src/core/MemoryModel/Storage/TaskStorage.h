//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKSTORAGE_H_
#define TODOLIST_SRC_API_TASKSTORAGE_H_

#include <map>
#include <MemoryModel/Task/TaskEntity.h>
#include <MemoryModel/Storage/TaskStorageInterface.h>

class TaskStorage : public TaskStorageInterface {
 public:
  bool                                              AddTask(const std::shared_ptr<TaskEntity>& task) override;
  bool                                              RemoveTask(const TaskID& id) override;

  std::shared_ptr<TaskEntity>                       GetTask(const TaskID& id) override;

 private:
  std::map<TaskID, std::shared_ptr<TaskEntity>>     tasks_;
};


#endif //TODOLIST_SRC_API_TASKFACTORY_H_
