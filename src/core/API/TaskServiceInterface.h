//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
#define TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_

#include <vector>
#include <src/core/API/OperationResult.h>
#include "TaskDTO.h"

class TaskServiceInterface {
 public:
  ~TaskServiceInterface() = default;

 public:
  virtual TaskDTO                 getTask(const unsigned int&) const = 0;
  virtual std::vector<TaskDTO>    getAllTasks(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksForToday(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksForWeek(const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByLabel(const std::string &, const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByName(const std::string&, const bool&) const = 0;
  virtual std::vector<TaskDTO>    getTasksByPriority(const Priority&) const = 0;

  virtual OperationResult         addTask(const TaskDTO&) = 0;
  virtual OperationResult         addSubtask(const unsigned int&, const TaskDTO&) = 0;
  virtual OperationResult         RemoveTask(const unsigned int&) = 0;
  virtual OperationResult         postponeTask(const unsigned int&, const boost::gregorian::date&) = 0;
  virtual OperationResult         completeTask(const unsigned int&) = 0;
};

#endif //TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
