//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <MemoryModel/ModelAPI/TaskModelInterface.h>

/*
 * \brief Entry point to work with the memory model.
 *
 * @see ModelTaskDTO.h
 *
 * @author Rodion Shyshkin
 */

class TaskModel : public TaskModelInterface {
 public:
  TaskModel();
  TaskModel(std::unique_ptr<TaskStorageInterface> storage,
            std::unique_ptr<TaskViewInterface> view,
            std::unique_ptr<IDGeneratorInterface> generator);

 public:
  /*
   * Gets single task.
   *
   * @param TaskID id.
   *
   * @return optional ModelTaskDTO data-transfer-object,
   * std::nullopt if there are no task with specified ID.
   */
  std::optional<ModelTaskDTO> GetTask(const TaskID &) const override;

  /*
   * Gets all tasks sorted by ID.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetAllTasks() const override;

  /*
   * Gets all tasks for current day.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetTasksForToday() const override;

  /*
   * Gets tasks for all future days until nearest Monday.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetTasksForWeek() const override;

  /*
   * Gets tasks with a particular label.
   *
   * @param std::string label.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetTasksByLabel(const std::string &label) const override;

  /*
   * Gets tasks with a particular name.
   *
   * @param std::string name.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetTasksByName(const std::string &name) const override;

  /*
   * Gets tasks with a particular priority.
   *
   * @param Priority priority.
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetTasksByPriority(const Priority &priority) const override;

  /*
   * Adds task to a system.
   *
   * @param ModelTaskDTO instance.
   *
   * @return OperationResult<StorageError> instance.
   * Method GetError() gives std::nullopt if operation is successful
   * or some error from StorageError enum in another case.
   */
  OperationResult<StorageError>     AddTask(const ModelTaskDTO& task) override;

  /*
   * Adds subtask to a system.
   *
   * @param TaskID id of parent
   * @param ModelTaskDTO instance.
   *
   * @return OperationResult<StorageError> instance.
   * Method GetError() gives std::nullopt if operation is successful
   * or some error from StorageError enum in another case.
   */
  OperationResult<StorageError>     AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;

  /*
   * Removes task with all tree of subtasks from a system.
   *
   * @param TaskID id
   *
   * @return OperationResult<StorageError> instance.
   * Method GetError() gives std::nullopt if operation is successful
   * or some error from StorageError enum in another case.
   */
  OperationResult<StorageError>     RemoveTask(const TaskID& id) override;

  /*
   * Completes task with all tree of subtasks.
   *
   * @param TaskID id
   *
   * @return True if success, False if task was not found.
   */
  bool                              CompleteTask(const TaskID &id) override;

  /*
   * Postpones task.
   *
   * @param TaskID id
   *
   * @return True if success, False if task was not found.
   */
  bool                              PostponeTask(const TaskID &id, const Date &newdate) override;

  /*
   * Gets all subtasks of a task.
   *
   * @param TaskID id
   *
   * @return ModelTaskDTO vector.
   */
  std::vector<ModelTaskDTO>         GetSubtasks(const TaskID &id) override;

 private:
  std::unique_ptr<TaskStorageInterface>      task_storage_;
  std::unique_ptr<TaskViewInterface>         task_view_;
  std::unique_ptr<IDGeneratorInterface>      generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
