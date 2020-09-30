//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <MemoryModel/Storage/TaskModelInterface.h>

class TaskModel : public TaskModelInterface {
 public:
  TaskModel();

 public:
  static std::unique_ptr<TaskModel> createByTasks(const std::vector<ModelTaskDTO>& tasks);

 public:
  TaskView                          GetTaskView() const override;
  TaskStorage                       GetTaskStorage() const override;

  OperationResult<StorageError>     AddTask(const ModelTaskDTO& task) override;
  OperationResult<StorageError>     AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;
  OperationResult<StorageError>     RemoveTask(const TaskID& id) override;

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  IDGenerator                       generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
