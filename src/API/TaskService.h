//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKMANAGER_H_
#define TODOLIST__TASKMANAGER_H_

#include "FullTask.h"
#include "GenerateID.h"
#include "FullTaskDTO.h"
#include <map>

class TaskService {
 public:
  TaskService();
  ~TaskService();

 public:
  std::vector<FullTaskDTO> getAllTasks() const;
  std::vector<FullTaskDTO> getTasksForToday() const;
  std::vector<FullTaskDTO> getTasksForWeek() const;
  std::vector<FullTaskDTO> getTasksForLabel(const std::string &label) const;


  void addTask(const Task &task);
  void addSubtask(const TaskID &id, const Task &subtask);
  void removeTask(const TaskID &id);


  void completeTask(const TaskID &id);
  void postponeTask(const TaskID &id, const DateTime &newtime);

 public:
  friend class TaskManagerDTO;

 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::shared_ptr<FullTask>, std::greater<Task::Priority>> sortedTasks;
  GenerateID newID;
};

#endif //TODOLIST__TASKMANAGER_H_
