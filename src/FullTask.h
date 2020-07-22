//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_FULLTASK_H_
#define TODOLIST_SRC_FULLTASK_H_

#include "Task.h"
#include "GenerateID.h"
#include "TaskID.h"
#include "UUID.h"

class FullTask {
 public:
  FullTask();
  FullTask(const Task &task, const TaskID &id);

 public:
  UUID getUUID() const;
  TaskID getUserID() const;
  std::string getName() const;
  std::string getLabel() const;
  Task::Priority getPriority() const;
  DueTime getTime() const;
  bool getStatus() const;
  Task getTask() const;
  std::vector<std::shared_ptr<FullTask>> getSubtasks() const;

 public:
  void AddSubtask(const std::shared_ptr<FullTask> &task);
  void setComplete();
  void postponeTask(const Task &newtask);

 public:
  void showTask();

 private:
  TaskID user_id;
  UUID id;
  bool status;
  std::shared_ptr<Task> task;
  std::vector<std::shared_ptr<FullTask>> subtasks;
};

#endif //TODOLIST_SRC_FULLTASK_H_
