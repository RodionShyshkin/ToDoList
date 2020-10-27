//
// Created by rodion on 8/17/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
#define TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_

#include <MemoryModel/Storage/TaskView.h>
#include <MemoryModel/Storage/TaskStorage.h>
#include <API/OperationResult/OperationResult.h>
#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <API/OperationResult/StorageError.h>

class TaskModelInterface {
 public:
  virtual ~TaskModelInterface() = default;

 public:

  virtual std::optional<ModelTaskDTO> GetTask(const TaskID&) const = 0;

  virtual std::vector<ModelTaskDTO>   GetAllTasks() const = 0;
  virtual std::vector<ModelTaskDTO>   GetTasksForToday() const = 0;
  virtual std::vector<ModelTaskDTO>   GetTasksForWeek() const = 0;
  virtual std::vector<ModelTaskDTO>   GetTasksByLabel(const std::string &label) const = 0;
  virtual std::vector<ModelTaskDTO>   GetTasksByName(const std::string& name) const = 0;
  virtual std::vector<ModelTaskDTO>   GetTasksByPriority(const Priority& priority) const = 0;

  virtual bool                        PostponeTask(const TaskID& id, const Date& newdate) = 0;
  virtual bool                        CompleteTask(const TaskID& id) = 0;

  virtual OperationResult<StorageError>  AddTask(const ModelTaskDTO& task) = 0;
  virtual OperationResult<StorageError>  AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) = 0;
  virtual OperationResult<StorageError>  RemoveTask(const TaskID& id) = 0;

  virtual std::vector<ModelTaskDTO>      GetSubtasks(const TaskID& id) = 0;
};

#endif //TODOLIST_SRC_MEMORYMODEL_STORAGE_FULLSTORAGEINTERFACE_H_
