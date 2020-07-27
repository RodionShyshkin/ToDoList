//
// Created by rodion on 7/23/20.
//

#ifndef TODOLIST_SRC_TASKMANAGERDTO_H_
#define TODOLIST_SRC_TASKMANAGERDTO_H_

#include "TaskService.h"

class TaskManagerDTO {
 public:
  TaskManagerDTO(const std::shared_ptr<TaskService> &dir);
  ~TaskManagerDTO();

 public:
  size_t getTasksAmount() const;
  std::vector<std::shared_ptr<FullTask>> getAllTasks() const;
  FullTaskDTO getTask(const TaskID &userid) const;

 private:
  std::shared_ptr<TaskService> dir;
};

#endif //TODOLIST_SRC_TASKMANAGERDTO_H_
