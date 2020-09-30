//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <MemoryModel/Storage/TaskModelInterface.h>

class TaskModel : public TaskModelInterface {
 public:
  TaskModel();

  TaskModel(std::unique_ptr<TaskStorageInterface> storage,
            std::unique_ptr<TaskViewInterface> view,
            std::unique_ptr<IDGeneratorInterface> generator);

 public:
  static std::unique_ptr<TaskModel> createByTasks(const std::vector<ModelTaskDTO>& tasks);

 public:
  TaskViewInterface&         GetTaskView() const override;
  TaskStorageInterface&      GetTaskStorage() const override;

  OperationResult<StorageError>     AddTask(const ModelTaskDTO& task) override;
  OperationResult<StorageError>     AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;
  OperationResult<StorageError>     RemoveTask(const TaskID& id) override;

  std::vector<ModelTaskDTO>         GetSubtasks(const TaskID &id) override;

 private:
  std::unique_ptr<TaskStorageInterface>      task_storage_;
  std::unique_ptr<TaskViewInterface>         task_view_;
  std::unique_ptr<IDGeneratorInterface>      generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
