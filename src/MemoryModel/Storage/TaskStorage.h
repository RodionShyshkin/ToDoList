//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKSTORAGE_H_
#define TODOLIST_SRC_API_TASKSTORAGE_H_

#include <MemoryModel/Task/TaskEntity.h>
#include <map>

class TaskStorage {
 public:
  bool                                              PushTask(const std::shared_ptr<TaskEntity>& task);
  bool                                              RemoveTask(const TaskID& id);

  bool                                              HasTask(const TaskID& id);
  std::shared_ptr<TaskEntity>                       GetTask(const TaskID& id);

 private:
  std::map<TaskID, std::shared_ptr<TaskEntity>>     tasks_;
};

#endif //TODOLIST_SRC_API_TASKFACTORY_H_
