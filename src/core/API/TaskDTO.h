//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_TASKDTO_H_
#define TODOLIST_SRC_TASKDTO_H_

#include <MemoryModel/Task/TaskID.h>
#include <iostream>
#include <API/Priority.h>
#include <MemoryModel/Task/Date.h>
#include <MemoryModel/Task/Task.h>

/*
 * Data-Transfer-Object class which contains information about task.
 *
 * @author: Rodion Shyshkin
 */

class TaskDTO {
 public:
  TaskDTO();

 public:
  /*
   * Factory method for TaskDTO instance.
   *
   * @param TaskID identifier of a task.
   *
   * @param Task task.
   *
   * @param bool status, True if task is completed, False in another case.
   *
   * @return TaskDTO instance.
   */
  static TaskDTO  create(const TaskID& id, const Task& task, const bool& status);

 public:
  TaskID          getID() const;
  std::string     getName() const;
  std::string     getLabel() const;
  Priority        getPriority() const;
  Date            getDueDate() const;
  bool            getStatus() const;

 private:
  TaskDTO(const TaskID& id, const Task& task, const bool& status);

 private:
  TaskID          task_id_;
  std::string     task_name_;
  std::string     task_label_;
  Priority        task_priority_;
  Date            task_due_date_;
  bool            task_status_;
};

#endif //TODOLIST_SRC_FULLTASKDTO_H_
