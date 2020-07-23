//
// Created by rodion on 7/23/20.
//

#ifndef TODOLIST_SRC_TASKMANAGERHIDDEN_H_
#define TODOLIST_SRC_TASKMANAGERHIDDEN_H_

#include "TaskManager.h"

class TaskManagerHidden {
 public:
  TaskManagerHidden(const std::shared_ptr<TaskManager> &dir);
  ~TaskManagerHidden();

 public:
  size_t getTasksAmount() const;
  std::vector<FullTaskDTO> getAllTasks() const;
  FullTaskDTO getTask(const TaskID &userid) const;

 private:
  std::shared_ptr<TaskManager> dir;
};

#endif //TODOLIST_SRC_TASKMANAGERHIDDEN_H_
