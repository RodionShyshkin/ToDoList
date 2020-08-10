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
  std::vector<TaskDTO>              getAllTasks();
  std::vector<TaskDTO>              getTasksForToday();
  std::vector<TaskDTO>              getTasksForWeek();
  std::vector<TaskDTO>              getTasksForLabel(const std::string &label);
  std::vector<TaskDTO>              getTasksForName(const std::string &name);
  std::optional<TaskDTO>            getTaskByID(const TaskID &id);

//  std::optional<TaskDTO>            AddTask(const Task &task);
  OperationResult                   AddTask(const Task &task);
  OperationResult                   AddSubtask(const TaskID &id, const Task &subtask);

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  GenerateID                        generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_TASKSERVICESTORAGE_H_
