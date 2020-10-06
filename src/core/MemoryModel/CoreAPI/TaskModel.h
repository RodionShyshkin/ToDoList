//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <src/core/MemoryModel/CoreAPI/TaskModelInterface.h>

class TaskModel : public TaskModelInterface {
 public:
  TaskModel();
  TaskModel(std::unique_ptr<TaskStorageInterface> storage,
            std::unique_ptr<TaskViewInterface> view,
            std::unique_ptr<IDGeneratorInterface> generator);
  TaskModel(TaskModel& model);

 public:
  ModelTaskDTO getTask(const TaskID &) const override;
  std::vector<ModelTaskDTO> getAllTasks() const override;
  std::vector<ModelTaskDTO> getTasksForToday() const override;
  std::vector<ModelTaskDTO> getTasksForWeek() const override;
  std::vector<ModelTaskDTO> getTasksByLabel(const std::string &label) const override;
  std::vector<ModelTaskDTO> getTasksByName(const std::string &name) const override;
  std::vector<ModelTaskDTO> getTasksByPriority(const Priority &priority) const override;

  OperationResult<StorageError>     AddTask(const ModelTaskDTO& task) override;
  OperationResult<StorageError>     AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;
  OperationResult<StorageError>     RemoveTask(const TaskID& id) override;

  bool                              completeTask(const TaskID &id) override;
  bool                              postponeTask(const TaskID &id, const Date &newdate) override;

  std::vector<ModelTaskDTO>         GetSubtasks(const TaskID &id) override;

 private:
  std::unique_ptr<TaskStorageInterface>      task_storage_;
  std::unique_ptr<TaskViewInterface>         task_view_;
  std::unique_ptr<IDGeneratorInterface>      generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_