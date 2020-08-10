//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASKSERVICE_H_
#define TODOLIST__TASKSERVICE_H_

#include "API/TaskDTO.h"
#include <map>
#include <optional>
#include <MemoryModel/TaskServiceStorage.h>

class TaskService {
 public:
  TaskService();

 public:
  std::vector<TaskDTO>              getAllTasks();
  std::vector<TaskDTO>              getTasksForToday();
  std::vector<TaskDTO>              getTasksForWeek();
  std::vector<TaskDTO>              getTasksForLabel(const std::string &label);

  std::optional<TaskDTO>            addTask(const Task &task);
  std::optional<TaskDTO>            addSubtask(const TaskID &id, const Task &subtask);


 private:
  TaskServiceStorage                task_service_storage_;
};

#endif //TODOLIST__TASKMANAGER_H_
