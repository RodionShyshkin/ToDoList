//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKSTORAGE_H_
#define TODOLIST_SRC_API_TASKSTORAGE_H_

#include <iostream>
#include <memory>
#include <MemoryModel/TaskEntity.h>
#include <map>

class TaskStorage {
 public:
  void                                              PushTask(const std::pair<TaskID, std::shared_ptr<TaskEntity>>& task);
  std::optional<std::shared_ptr<TaskEntity>>        GetTask(const TaskID& id);
  bool                                              HasTask(const TaskID& id);

 private:
  std::map<TaskID, std::shared_ptr<TaskEntity>>     tasks_;
};

#endif //TODOLIST_SRC_API_TASKFACTORY_H_