//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
#define TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_

#include <vector>
#include <API/OperationResult/OperationResult.h>
#include <API/OperationResult/StorageError.h>
#include <API/OperationResult/PersistError.h>
#include "TaskDTO.h"

class TaskServiceInterface {
 public:
  ~TaskServiceInterface() = default;

 public:
  virtual std::optional<TaskDTO>  GetTask(const unsigned int&) const = 0;
  virtual std::vector<TaskDTO>    GetAllTasks(const bool&) const = 0;
  virtual std::vector<TaskDTO>    GetTasksForToday(const bool&) const = 0;
  virtual std::vector<TaskDTO>    GetTasksForWeek(const bool&) const = 0;
  virtual std::vector<TaskDTO>    GetTasksByLabel(const std::string &, const bool&) const = 0;
  virtual std::vector<TaskDTO>    GetTasksByName(const std::string&, const bool&) const = 0;
  virtual std::vector<TaskDTO>    GetTasksByPriority(const Priority&) const = 0;

  virtual OperationResult<StorageError>         AddTask(const TaskDTO&) = 0;
  virtual OperationResult<StorageError>         AddSubtask(const unsigned int&, const TaskDTO&) = 0;
  virtual OperationResult<StorageError>         RemoveTask(const unsigned int&) = 0;
  virtual bool         PostponeTask(const unsigned int&, const boost::gregorian::date&) = 0;
  virtual bool         CompleteTask(const unsigned int&) = 0;

  virtual OperationResult<PersistError>   Save(const std::string&) = 0;
  virtual OperationResult<PersistError>   Load(const std::string&) = 0;
};

#endif //TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
