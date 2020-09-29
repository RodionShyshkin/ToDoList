//
// Created by rodion on 9/29/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_

#include <string>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <src/core/API/Priority.h>
#include <src/core/MemoryModel/Task/Date.h>
#include <src/core/MemoryModel/Task/TaskID.h>

class ModelTaskDTO {
 public:
  ModelTaskDTO();

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
  static ModelTaskDTO  create(const TaskID& id, const std::string& name, const std::string& label,
                         const Priority& priority, const Date& date, const bool& status);

 public:
  TaskID                            getID() const;
  std::string                       getName() const;
  std::string                       getLabel() const;
  Priority                          getPriority() const;
  Date                              getDueDate() const;
  bool                              getStatus() const;

 private:
  ModelTaskDTO(const TaskID& id, const std::string& name, const std::string& label,
          const Priority& priority, const Date& date, const bool& status);

 private:
  TaskID                  task_id_;
  std::string             task_name_;
  std::string             task_label_;
  Priority                task_priority_;
  Date                    task_due_date_;
  bool                    task_status_;
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_
