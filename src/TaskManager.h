//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKMANAGER_H_
#define TODOLIST__TASKMANAGER_H_

#include "FullTask.h"
#include "GenerateID.h"
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
  void addSubtask(const TaskID &id, const Task &subtask);
  void removeTask(const TaskID &id);

 public:
  void completeTask(const TaskID &id);
  void postponeTask(const TaskID &id, const DateTime &newtime);

 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::shared_ptr<FullTask>, std::greater<Task::Priority>> sortedTasks;

  GenerateID newID;
};

std::vector<std::shared_ptr<FullTask>>::const_iterator findIteratorInVector(std::vector<std::shared_ptr<FullTask>> vec, std::shared_ptr<FullTask> task);

std::multimap<Task::Priority, std::shared_ptr<FullTask>, std::greater<Task::Priority>>::const_iterator findIteratorInMultimap(std::shared_ptr<FullTask> task);
#endif //TODOLIST__TASKMANAGER_H_
