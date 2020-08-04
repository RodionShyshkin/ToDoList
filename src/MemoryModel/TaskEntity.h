//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_FULLTASK_H_
#define TODOLIST_SRC_FULLTASK_H_

#include "Task.h"
#include "GenerateID.h"
#include "TaskID.h"

class TaskEntity {
 public:
  TaskEntity();
  TaskEntity(const Task &task, const TaskID &id);

 public:
  TaskID                                     getID() const;
  [[nodiscard]] std::string                                getName() const;
  [[nodiscard]] std::string                                getLabel() const;
  [[nodiscard]] Task::Priority                             getPriority() const;
  [[nodiscard]] DueTime                                    getDueTime() const;
  [[nodiscard]] bool                                       getStatus() const;
  [[nodiscard]] Task                                       getTask() const;
  [[nodiscard]] std::vector<std::shared_ptr<TaskEntity>>   getSubtasks() const;

 public:
  void             AddSubtask(const std::shared_ptr<TaskEntity> &task);
  void             setComplete();
  void             substituteTask(const Task &newtask);

 private:
  TaskID                                                   user_id;
  bool                                                     status;
  Task                                                     task;
  std::vector<std::shared_ptr<TaskEntity>>                 subtasks;
};

#endif //TODOLIST_SRC_FULLTASK_H_
