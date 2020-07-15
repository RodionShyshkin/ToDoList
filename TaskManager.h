//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKMANAGER_H_
#define TODOLIST__TASKMANAGER_H_

#include "Task.h"
#include <map>

class TaskManager {
 public:
  TaskManager();
  ~TaskManager();

 public:
  void showAllTasks() const;
  void showTasksForToday() const;
  void showTasksForWeek() const;
  void showTasksForLabel(const std::string &label) const;

 public:
  void addTask(const Task &task);
  void addSubtask(std::shared_ptr<Task> root, Task &subtask);
  void removeTask();

  void markTask();

 private:
  std::vector<std::shared_ptr<Task>> tasks;
  std::multimap<Priority, std::shared_ptr<Task>, std::greater<Priority>> sortedTasks;
};

#endif //TODOLIST__TASKMANAGER_H_
