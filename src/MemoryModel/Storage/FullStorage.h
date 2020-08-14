//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <API/TaskDTO.h>
#include "TaskStorage.h"
#include "TaskView.h"
#include "OperationResult.h"

class FullStorage {
 public:
  FullStorage();

 public:
  TaskView                          GetTaskView() const;
  TaskStorage                       GetTaskStorage() const;

  OperationResult                   AddTask(const Task &task);
  OperationResult                   AddSubtask(const TaskID &id, const Task &subtask);
  OperationResult                   RemoveTask(const TaskID& id);

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  IDGenerator                       generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
