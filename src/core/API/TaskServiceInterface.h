//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
#define TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_

#include <vector>
#include <MemoryModel/Storage/OperationResult.h>
#include "TaskDTO.h"

class TaskServiceInterface {
 public:
  ~TaskServiceInterface() = default;

 public:
  virtual std::vector<TaskDTO>    getAllTasks(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksForToday(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksForWeek(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByLabel(const std::string &, const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByName(const std::string&, const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByPriority(const Priority&) const = 0;
  virtual OperationResult         addTask(const TaskDTO&) = 0;
  virtual OperationResult         addSubtask(const TaskID&, const TaskDTO&) = 0;
  virtual OperationResult         RemoveTask(const TaskID&) = 0;
  virtual OperationResult         postponeTask(const TaskID&, const Date&) = 0;
  virtual OperationResult         completeTask(const TaskID&) = 0;
};

#endif //TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
