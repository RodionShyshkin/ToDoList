//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_TASKDTO_H_
#define TODOLIST_SRC_TASKDTO_H_

#include <MemoryModel/TaskID.h>
#include "MemoryModel/Task.h"

class TaskDTO {
 public:
  TaskDTO();
  TaskDTO(const TaskID& id, const Task& task, const bool& status);

 public:
  TaskID getID() const;
  std::string getName() const;
  std::string getLabel() const;
  Task::Priority getPriority() const;
  DateTime getDueDate() const;
  bool getStatus() const;

 private:
  TaskID          task_id_;
  std::string     task_name_;
  std::string     task_label_;
  Task::Priority  task_priority_;
  DateTime        task_due_date_;
  bool            task_status_;
};

#endif //TODOLIST_SRC_FULLTASKDTO_H_
