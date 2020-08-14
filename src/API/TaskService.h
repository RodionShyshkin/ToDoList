//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKSERVICE_H_
#define TODOLIST__TASKSERVICE_H_

#include "API/TaskDTO.h"
#include <MemoryModel/Storage/FullStorage.h>

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

  std::vector<TaskDTO>              getTasksByLabel(const std::string &label);
  std::vector<TaskDTO>              getTasksByName(const std::string& name);
  std::vector<TaskDTO>              getTasksByPriority(const Priority& priority);

  OperationResult                   addTask(const Task &task);
  OperationResult                   addSubtask(const TaskID &id, const Task &subtask);
  OperationResult                   RemoveTask(const TaskID& id);

  OperationResult                   postponeTask(const TaskID& id, const Date& newdate);
  OperationResult                   completeTask(const TaskID& id);

  std::vector<TaskEntity>           getDebug();
  TaskStorage                       getDebug2();

 private:
  FullStorage                task_service_storage_;
};

#endif //TODOLIST__TASKMANAGER_H_
