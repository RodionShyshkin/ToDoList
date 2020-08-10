//
// Created by rodion on 7/15/20.
//

#include "TaskService.h"

/*
 * API for working with tasks.
 */

TaskService::TaskService() : task_service_storage_(TaskServiceStorage()) {}

/*
 * @param [none]
 *
 * @return vector of TaskDTO instances which forms all tasks user had added.
 */
std::vector<TaskDTO> TaskService::getAllTasks() {
  return task_service_storage_.getAllTasks();
}

/*
 * @param [none]
 *
 * @return vector of TaskDTO instances which forms all tasks for current day (local date).
 */

std::vector<TaskDTO> TaskService::getTasksForToday() {
  return task_service_storage_.getTasksForToday();
}

/*
 * @param [none]
 *
 * @return vector of TaskDTO instances which forms all tasks for this week (until the next Monday).
 */

std::vector<TaskDTO> TaskService::getTasksForWeek() {
  return task_service_storage_.getTasksForWeek();
}

/*
 * @param label   Task field
 *
 * @return vector of TaskDTO instances which forms all tasks which have label from parameter.
 */

std::vector<TaskDTO> TaskService::getTasksForLabel(const std::string &label) {
  return task_service_storage_.getTasksForLabel(label);
}

/*
 * Adding a new task.
 *
 * @param Task    Task instance
 *
 * @see OperationResult.h
 * @return the result of adding Task
 */

OperationResult TaskService::addTask(const Task &task) {
  return task_service_storage_.AddTask(task);
}

/*
 * Adding subtask for an existing task.
 *
 * @param TaskID  id of parent task, for which we are going to add subtask.
 * @param Task    Task instance
 *
 * @see OperationResult.h
 * @return the result of adding Task
 */

OperationResult TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  return task_service_storage_.AddSubtask(id, subtask);
}
