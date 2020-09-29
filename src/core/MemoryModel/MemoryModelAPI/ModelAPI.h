//
// Created by rodion on 9/29/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPI_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPI_H_

#include <src/core/MemoryModel/Storage/TaskModel.h>
#include "ModelAPIInterface.h"
#include "ModelTaskDTO.h"

class ModelAPI : public ModelAPIInterface {
 public:
  ModelAPI();

 public:
  ModelTaskDTO                      getTask(const TaskID&) const override;

  std::vector<ModelTaskDTO>         getAllTasks() const override;
  std::vector<ModelTaskDTO>         getTasksForToday() const override;
  std::vector<ModelTaskDTO>         getTasksForWeek() const override;
  std::vector<ModelTaskDTO>         getTasksByLabel(const std::string &label) const override;
  std::vector<ModelTaskDTO>         getTasksByName(const std::string &name) const override;
  std::vector<ModelTaskDTO>         getTasksByPriority(const Priority &priority) const override;

  OperationResult                   addTask(const ModelTaskDTO& task) override;
  OperationResult                   addSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;
  OperationResult                   RemoveTask(const TaskID& id) override;
  OperationResult                   postponeTask(const TaskID& id, const Date& newdate) override;
  OperationResult                   completeTask(const TaskID& id) override;

 private:
  std::unique_ptr<TaskModel> model_;
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELAPI_H_
