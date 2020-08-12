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
  return task_service_storage_.GetAllTasks();
}

/*
 * @param [none]
 *
 * @return vector of TaskDTO instances which forms all tasks for current day (local date).
 */

std::vector<TaskDTO> TaskService::getTasksForToday() {
  return task_service_storage_.GetTasksForToday();
}

/*
 * @param [none]
 *
 * @return vector of TaskDTO instances which forms all tasks for this week (until the next Monday).
 */

std::vector<TaskDTO> TaskService::getTasksForWeek() {
  return task_service_storage_.GetTasksForWeek();
}

/*
 * @param label_   Task field
 *
 * @return vector of TaskDTO instances which forms all tasks which have label_ from parameter.
 */

std::vector<TaskDTO> TaskService::getTasksForLabel(const std::string &label) {
  return task_service_storage_.GetTasksForLabel(label);
}

/*
 * Adding a new task_.
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
 * Adding subtask for an existing task_.
 *
 * @param TaskID  id of parent task_, for which we are going to add subtask.
 * @param Task    Task instance
 *
 * @see OperationResult.h
 * @return the result of adding Task
 */

OperationResult TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  return task_service_storage_.AddSubtask(id, subtask);
}
