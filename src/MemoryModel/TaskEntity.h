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
  static TaskEntity                                       create(const Task& task, const TaskID& id);

 public:
  TaskID                                                  GetID() const;
  std::string                                             GetName() const;
  std::string                                             GetLabel() const;
  Priority                                                GetPriority() const;
  Date                                                    GetDueTime() const;
  bool                                                    GetStatus() const;
  Task                                                    GetTask() const;
  std::vector<std::shared_ptr<TaskEntity>>                GetSubtasks() const;

 public:
  void                                                    AddSubtask(const std::shared_ptr<TaskEntity> &task);
  void                                                    SetComplete();
  void                                                    SubstituteTask(const Task &newtask);

 private:
  TaskEntity(const Task &task, const TaskID &id);

 private:
  TaskID                                                  user_id_;
  bool                                                    status_;
  Task                                                    task_;
  std::vector<std::shared_ptr<TaskEntity>>                subtasks_;
};

#endif //TODOLIST_SRC_FULLTASK_H_
