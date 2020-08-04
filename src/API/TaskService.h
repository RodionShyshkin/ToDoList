//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKMANAGER_H_
#define TODOLIST__TASKMANAGER_H_

#include "TaskEntity.h"
#include "GenerateID.h"
#include "TaskDTO.h"
#include "TaskView.h"
#include "TaskOwner.h"
#include <map>

class TaskService {
 public:
  TaskService();
  ~TaskService();

 public:
  std::vector<TaskDTO>              getAllTasks();
  std::vector<TaskDTO>              getTasksForToday();
  std::vector<TaskDTO>              getTasksForWeek();
  std::vector<TaskDTO>              getTasksForLabel(const std::string &label);
  TaskDTO                           getTaskByID(const TaskID &id);


  void                              addTask(const Task &task);
  bool                              addSubtask(const TaskID &id, const Task &subtask);
//  void                              removeTask(const TaskID &id);


//  void                              completeTask(const TaskID &id);
//  void                              postponeTask(const TaskID &id, const DateTime &newtime);

 private:
  TaskView                          task_view_;
  TaskOwner                         owner_;
};

#endif //TODOLIST__TASKMANAGER_H_
