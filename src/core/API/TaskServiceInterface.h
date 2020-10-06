//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
#define TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_

#include <vector>
#include <src/core/API/OperationResult/OperationResult.h>
#include <src/core/Persister/SerializationError.h>
#include <src/core/API/OperationResult/StorageError.h>
#include <src/core/API/OperationResult/PersistError.h>
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

  virtual OperationResult<StorageError>         addTask(const TaskDTO&) = 0;
  virtual OperationResult<StorageError>         addSubtask(const unsigned int&, const TaskDTO&) = 0;
  virtual OperationResult<StorageError>         RemoveTask(const unsigned int&) = 0;
  virtual bool         postponeTask(const unsigned int&, const boost::gregorian::date&) = 0;
  virtual bool         completeTask(const unsigned int&) = 0;

  virtual OperationResult<PersistError>   Save(const std::string&) = 0;
  virtual OperationResult<PersistError>   Load(const std::string&) = 0;
};

#endif //TODOLIST_SRC_CORE_API_TASKSERVICEINTERFACE_H_
