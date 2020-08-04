//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKFACTORY_H_
#define TODOLIST_SRC_API_TASKFACTORY_H_

#include <iostream>
#include <memory>
#include <TaskEntity.h>
#include <map>

class TaskOwner {
 public:
  TaskOwner();
  ~TaskOwner();

 public:
  TaskID generateID();
  void pushTask(const std::pair<TaskID, std::shared_ptr<TaskEntity>>& task);

  bool if_exist(const TaskID& id);

 private:
  std::map<TaskID, std::shared_ptr<TaskEntity>>     tasks;
  GenerateID                                        newID;
};

#endif //TODOLIST_SRC_API_TASKFACTORY_H_
