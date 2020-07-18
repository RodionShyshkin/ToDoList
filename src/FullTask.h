//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_FULLTASK_H_
#define TODOLIST_SRC_FULLTASK_H_

#include "Task.h"
#include "GenerateID.h"
#include "TaskID.h"

class FullTask {
 public:
  FullTask();
//  FullTask(std::shared_ptr<Task> task);
  FullTask(const Task &task, const TaskID &id);

 public:
  TaskID getID() const;
  bool getStatus() const;
  std::string getLabel() const;
  Task::Priority getPriority() const;
  std::vector<std::shared_ptr<FullTask>> getSubtasks() const;

 public:
  void AddSubtask(const std::shared_ptr<FullTask> &task);
  void setComplete();

 public:
  void showTask();

 private:
  TaskID id;
  bool status;
  std::shared_ptr<Task> task;
  std::vector<std::shared_ptr<FullTask>> subtasks;
};

#endif //TODOLIST_SRC_FULLTASK_H_
