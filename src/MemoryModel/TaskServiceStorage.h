//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_TASKSERVICESTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_TASKSERVICESTORAGE_H_

#include <API/TaskDTO.h>
#include "MemoryModel/TaskStorage.h"
#include "MemoryModel/TaskView.h"
#include "OperationResult.h"

class TaskServiceStorage {
 public:
  TaskServiceStorage();

 public:
  std::vector<TaskDTO>              GetAllTasks();
  std::vector<TaskDTO>              GetTasksForToday();
  std::vector<TaskDTO>              GetTasksForWeek();
  std::vector<TaskDTO>              GetTasksForLabel(const std::string &label);
  std::vector<TaskDTO>              GetTasksForName(const std::string &name);
  std::optional<TaskDTO>            GetTaskById(const TaskID &id);

  OperationResult                   AddTask(const Task &task);
  OperationResult                   AddSubtask(const TaskID &id, const Task &subtask);

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  IDGenerator                       generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_TASKSERVICESTORAGE_H_
