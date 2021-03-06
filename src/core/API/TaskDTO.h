//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_TASKDTO_H_
#define TODOLIST_SRC_TASKDTO_H_

#include <iostream>
#include <API/Priority.h>
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
   * @param uint32 identifier of a task.
   * @param std::string name.
   * @param std::string label.
   * @param Priority priority
   * @param boost::gregorian::date date.
   * @param bool status, True if task is completed, False in another case.
   *
   * @return TaskDTO instance.
   */
  static TaskDTO  Create(const unsigned int& id, const std::string& name, const std::string& label,
                         const Priority& priority, const boost::gregorian::date& date, const bool& status);

 public:
  unsigned int                      getID() const;
  std::string                       getName() const;
  std::string                       getLabel() const;
  Priority                          getPriority() const;
  boost::gregorian::date            getDueDate() const;
  bool                              getStatus() const;

 private:
  TaskDTO(const unsigned int& id, const std::string& name, const std::string& label,
          const Priority& priority, const boost::gregorian::date& date, const bool& status);

 private:
  unsigned int    task_id_;
  std::string     task_name_;
  std::string     task_label_;
  Priority        task_priority_;
  boost::gregorian::date task_due_date_;
  bool            task_status_;
};

#endif //TODOLIST_SRC_FULLTASKDTO_H_
