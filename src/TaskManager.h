//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKMANAGER_H_
#define TODOLIST__TASKMANAGER_H_

#include "FullTask.h"
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
  void addTask(const FullTask &task);
  void addSubtask(const unsigned int &id, FullTask &subtask);
  void removeTask(const unsigned int &id);

  void markTask(const unsigned int &id);

 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::shared_ptr<FullTask>, std::greater<Task::Priority>> sortedTasks;
};

#endif //TODOLIST__TASKMANAGER_H_
