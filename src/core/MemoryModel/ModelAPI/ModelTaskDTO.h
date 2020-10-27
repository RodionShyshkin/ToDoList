//
// Created by rodion on 9/29/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_

#include <string>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <API/Priority.h>
#include <MemoryModel/Task/Date.h>
#include <MemoryModel/Task/TaskID.h>

/*
 * Data transfer object which contains information about task
 * and which is accessful only in Memory Model.
 *
 * @author Rodion Shyshkin
 */

class ModelTaskDTO {
 public:
  ModelTaskDTO();

 public:
  /*
   * Factory method for ModelTaskDTO instance which is subtask of some task.
   *
   * @param TaskID identifier of a task.
   * @param std::string name.
   * @param std::string label.
   * @param Priority priority.
   * @param Date date.
   * @param bool Status(true if completed, false in another case).
   * @param TaskID parent task.
   *
   * @return ModelTaskDTO instance.
   */
  static ModelTaskDTO     CreateWithParent(const TaskID& id, const std::string& name, const std::string& label,
                                           const Priority& priority, const Date& date, const bool& status, const TaskID& parent);

  /*
   * Factory method for ModelTaskDTO instance which is not subtask of any task.
   *
   * @param TaskID identifier of a task.
   * @param std::string name.
   * @param std::string label.
   * @param Priority priority.
   * @param Date date.
   * @param bool Status(true if completed, false in another case).
   *
   * @return ModelTaskDTO instance.
   */
  static ModelTaskDTO     CreateWithoutParent(const TaskID& id, const std::string& name, const std::string& label,
                                              const Priority& priority, const Date& date, const bool& status);

 public:
  TaskID                  GetID() const;
  TaskID                  GetParentID() const;
  std::string             GetName() const;
  std::string             GetLabel() const;
  Priority                GetPriority() const;
  Date                    GetDueDate() const;
  bool                    GetStatus() const;

 private:
  ModelTaskDTO(const TaskID& id, const std::string& name, const std::string& label,
          const Priority& priority, const Date& date, const bool& status, const TaskID& parent);

 private:
  TaskID                  task_id_;
  TaskID                  parent_id_;
  std::string             task_name_;
  std::string             task_label_;
  Priority                task_priority_;
  Date                    task_due_date_;
  bool                    task_status_;
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_MEMORYMODELAPI_MODELTASKDTO_H_
