//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKSERVICE_H_
#define TODOLIST__TASKSERVICE_H_

#include "API/TaskDTO.h"
#include <map>
#include <optional>
#include <MemoryModel/TaskServiceStorage.h>

/*
 * API for work with tasks.
 *
 * @see TaskService.cpp
 *
 * @author: Rodion Shyshkin
 */

class TaskService {
 public:
  TaskService();

 public:
  std::vector<TaskDTO>              getAllTasks();
  std::vector<TaskDTO>              getTasksForToday();
  std::vector<TaskDTO>              getTasksForWeek();
  std::vector<TaskDTO>              getTasksForLabel(const std::string &label);

  OperationResult                   addTask(const Task &task);
  OperationResult                   addSubtask(const TaskID &id, const Task &subtask);


 private:
  TaskServiceStorage                task_service_storage_;
};

#endif //TODOLIST__TASKMANAGER_H_
