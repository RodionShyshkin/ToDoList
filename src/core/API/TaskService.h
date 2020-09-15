//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKSERVICE_H_
#define TODOLIST__TASKSERVICE_H_

#include "TaskDTO.h"
#include "TaskServiceInterface.h"
#include <MemoryModel/Storage/FullStorage.h>

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

 public:
  TaskDTO                           getTask(const TaskID& id) const override;
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
  OperationResult                   addTask(const TaskDTO& task) override;

  /*
   * \brief Adds subtask for a task which already exists.
   *
   * @param TaskID identifier of a task for which you are going to add subtask.
   *
   * @param TaskDTO obbject with internal subtask information.
   *
   * @return OperationResult information about result of adding (contains error or message about success).
   */
  OperationResult                   addSubtask(const TaskID &id, const TaskDTO& subtask) override;

  /*
   * \brief Removes task.
   *
   * @param TaskID identifier of a task which you are going to delete.
   *
   * @return OperationResult information about result of removing (contains error or message about success).
   */
  OperationResult                   RemoveTask(const TaskID& id) override;

  /*
   * \brief Postpones task.
   *
   * @param TaskID identifier of a task in which you are going to change date.
   *
   * @param Date New deadline for task.
   *
   * @return OperationResult information about result of postpone (contains error or message about success).
   */
  OperationResult                   postponeTask(const TaskID& id, const Date& newdate) override;

  /*
   * \brief Completes task.
   *
   * @param TaskID identifier of a task you want to mark as completed.
   *
   * @return OperationResult information about result of completing (contains error or message about success).
   */
  OperationResult                   completeTask(const TaskID& id) override;

 private:
  static std::vector<TaskDTO>       sortedByPriority(std::vector<TaskDTO> vector);

 private:
  FullStorage                task_service_storage_;
};

#endif //TODOLIST__TASKMANAGER_H_
