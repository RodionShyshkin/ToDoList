//
// Created by rodion on 9/29/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPIINTERFACE_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPIINTERFACE_H_

#include <vector>
#include <src/core/MemoryModel/Storage/OperationResult.h>
#include "ModelTaskDTO.h"
class ModelAPIInterface {
 public:
  virtual ~ModelAPIInterface() = default;

 public:
  virtual ModelTaskDTO        getTask(const TaskID&) const = 0;

  virtual std::vector<ModelTaskDTO>              getAllTasks() const = 0;
  virtual std::vector<ModelTaskDTO>              getTasksForToday() const = 0;
  virtual std::vector<ModelTaskDTO>              getTasksForWeek() const = 0;
  virtual std::vector<ModelTaskDTO>              getTasksByLabel(const std::string &label) const = 0;
  virtual std::vector<ModelTaskDTO>              getTasksByName(const std::string& name) const = 0;
  virtual std::vector<ModelTaskDTO>              getTasksByPriority(const Priority& priority) const = 0;

  virtual OperationResult                   addTask(const ModelTaskDTO& task) = 0;
  virtual OperationResult                   addSubtask(const TaskID &id, const ModelTaskDTO& subtask) = 0;
  virtual OperationResult                   RemoveTask(const TaskID& id) = 0;
  virtual OperationResult                   postponeTask(const TaskID& id, const Date& newdate) = 0;
  virtual OperationResult                   completeTask(const TaskID& id) = 0;
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPIINTERFACE_H_
