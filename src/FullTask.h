//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_FULLTASK_H_
#define TODOLIST_SRC_FULLTASK_H_

#include "Task.h"
#include "taskID.h"

class FullTask {
 public:
  FullTask();
  FullTask(std::shared_ptr<Task> task);

 public:
  std::shared_ptr<FullTask> getRootTask() const;
  std::string getRootTaskName() const;
  std::vector<std::shared_ptr<FullTask>> getSubtasks() const;

 public:
  void pushSubtask(const FullTask &task);
  void setRoot(std::shared_ptr<FullTask> root);

  void setID();
  unsigned int getID();

 public:
  void showTask();

  std::shared_ptr<Task> task;
 private:
  unsigned int id;
  std::vector<std::shared_ptr<FullTask>> subtasks;
  std::shared_ptr<FullTask> rootTask;
};

#endif //TODOLIST_SRC_FULLTASK_H_
