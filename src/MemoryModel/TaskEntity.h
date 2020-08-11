//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_TASKENTITY_H_
#define TODOLIST_SRC_TASKENTITY_H_

#include "Task.h"
#include "IDGenerator.h"
#include "TaskID.h"

class TaskEntity {
 public:
  TaskEntity();

 public:
  static TaskEntity                          create(const Task& task, const TaskID& id);

 public:
  TaskID                                     getID() const;
  std::string                                getName() const;
  std::string                                getLabel() const;
  Priority                                   getPriority() const;
  DateTime                                   getDueTime() const;
  bool                                       getStatus() const;
  Task                                       getTask() const;
  std::vector<std::shared_ptr<TaskEntity>>   getSubtasks() const;

 public:
  void             AddSubtask(const std::shared_ptr<TaskEntity> &task);
  void             setComplete();
  void             substituteTask(const Task &newtask);

 private:
  TaskEntity(const Task &task, const TaskID &id);

 private:
  TaskID                                                   user_id;
  bool                                                     status;
  Task                                                     task;
  std::vector<std::shared_ptr<TaskEntity>>                 subtasks;
};

#endif //TODOLIST_SRC_FULLTASK_H_
