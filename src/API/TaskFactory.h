//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKFACTORY_H_
#define TODOLIST_SRC_API_TASKFACTORY_H_

#include <iostream>
#include <memory>
#include <TaskEntity.h>
#include <map>

class TaskFactory {
 public:
  TaskFactory();
  ~TaskFactory();

 public:
  std::shared_ptr<TaskEntity> addTask(const Task &task);
  std::optional<std::shared_ptr<TaskEntity>> addSubtask(const TaskID &id, const Task &subtask);

 private:
  std::map<TaskID, std::shared_ptr<TaskEntity>> tasks;
  GenerateID newID;
};

#endif //TODOLIST_SRC_API_TASKFACTORY_H_
