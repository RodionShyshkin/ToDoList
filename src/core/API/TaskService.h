//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKSERVICE_H_
#define TODOLIST__TASKSERVICE_H_

#include "TaskDTO.h"
#include "TaskServiceInterface.h"
#include <MemoryModel/ModelAPI/TaskModel.h>

/*
 * \brief Entry point for tasks management.
 *
 * @see TaskDTO.h
 *
 * @author: Rodion Shyshkin
 */

class TaskService : public TaskServiceInterface {
 public:
  TaskService();
  TaskService(std::unique_ptr<TaskModelInterface> model);

 public:
  /*
   * \brief Gives a task by its ID.
   *
   * @param uint32 identifier of the task
   *
   * @return TaskDTO object
   */
  std::optional<TaskDTO> getTask(const unsigned int& id) const override;
  /*
   * \brief Gives all actual tasks.
   *
   * @param bool flag for sorting tasks by priority
   *
   * @return TaskDTO vector Vector which contains all tasks, if param is true they are sorted by priority, in
   * another case they are not
   */
  std::vector<TaskDTO>              getAllTasks(const bool& sortByPriority) const override;

  /*
   * \brief Gives all tasks for today by local time.
   *
   * @param bool flag for sorting tasks by priority
   *
   * @return TaskDTO vector which contains all tasks for today, if param is true they are sorted by priority, in
   * another case they are not
   */
  std::vector<TaskDTO>              getTasksForToday(const bool& sortByPriority) const override;

  /*
   * \brief Gives all tasks for current week until Monday by local time.
   *
   * @param bool flag for sorting tasks by priority
   *
   * @return TaskDTO vector which contains all tasks for this week, if param is true they are sorted by priority, in
   * another case they are not
   */
  std::vector<TaskDTO>              getTasksForWeek(const bool& sortByPriority) const override;

  /*
   * \brief Gives all tasks with label which is pointed as parameter.
   *
   * @param string label
   * @param bool flag for sorting tasks by priority
   *
   * @return TaskDTO vector which contains all tasks with this label
   */
  std::vector<TaskDTO>              getTasksByLabel(const std::string &label, const bool& sortByPriority) const override;

  /*
   * \brief Gives all tasks with name which is pointed as parameter.
   *
   * @param string name
   * @param bool flag for sorting tasks by priority
   *
   * @return TaskDTO vector which contains all tasks with this name
   */
  std::vector<TaskDTO>              getTasksByName(const std::string& name, const bool& sortByPriority) const override;

  /*
   * \brief Gives all tasks with priority which is pointed as parameter.
   *
   * @param Priority priority (EMPTY, LOW, MEDIUM, HIGH).
   *
   * @return TaskDTO vector which contains all tasks with this priority.
   */
  std::vector<TaskDTO>              getTasksByPriority(const Priority& priority) const override;

  /*
   * \brief Adds task.
   *
   * @param TaskDTO object with internal task information.
   *
   * @return OperationResult information about result of adding (contains error or message about success).
   */
  OperationResult<StorageError>                   addTask(const TaskDTO& task) override;

  /*
   * \brief Adds subtask for a task which already exists.
   *
   * @param uint32 identifier of a task for which you are going to add subtask.
   *
   * @param TaskDTO obbject with internal subtask information.
   *
   * @return OperationResult information about result of adding (contains error or message about success).
   */
  OperationResult<StorageError>                   addSubtask(const unsigned int& id, const TaskDTO& subtask) override;

  /*
   * \brief Removes task.
   *
   * @param uint32 identifier of a task which you are going to delete.
   *
   * @return OperationResult information about result of removing (contains error or message about success).
   */
  OperationResult<StorageError>                   RemoveTask(const unsigned int& id) override;

  /*
   * \brief Postpones task.
   *
   * @param TaskID identifier of a task in which you are going to change date.
   *
   * @param Date New deadline for task.
   *
   * @return bool result (true if successful, false in another case).
   */
  bool                   postponeTask(const unsigned int& id, const boost::gregorian::date& newdate) override;

  /*
   * \brief Completes task.
   *
   * @param uint32 identifier of a task you want to mark as completed.
   *
   * @return bool result (true if successful, false in another case).
   */
  bool                   completeTask(const unsigned int& id) override;

  /*
   * \brief Saves tasks to a file.
   *
   * @param std::string file path
   *
   * @return OperationResult result of operation. std::nullopt if there is no errors
   * or PersistError if something went wrong.
   */
  OperationResult<PersistError> Save(const std::string &filepath) override;

  /*
   * \brief Load tasks from a file.
   *
   * @param std::string file path
   *
   * @return OperationResult result of operation. std::nullopt if there is no errors
   * or PersistError if something went wrong.
   */
  OperationResult<PersistError> Load(const std::string &filepath) override;

 private:
  static std::vector<TaskDTO>       sortedByPriority(std::vector<TaskDTO> vector);

  static TaskDTO                    convertFromModelDTO(const ModelTaskDTO& model_dto);
  static ModelTaskDTO               convertToModelDTO(const TaskDTO& dto);

 private:
  std::unique_ptr<TaskModelInterface>         model_api_;
};

#endif //TODOLIST__TASKMANAGER_H_
