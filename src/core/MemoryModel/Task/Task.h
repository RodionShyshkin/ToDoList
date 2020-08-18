//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include "Date.h"
#include "Priority.h"

/*
 * \brief Basic class which holds task.
 *
 * @author Rodion Shyshkin
 */

class Task {
 public:
  Task();

 public:
  /*
   * Factory method for task.
   *
   * @param std::string Task Name
   * @param std::string Task label
   * @param Priority Task priority (EMPTY, LOW, MEDIUM, HIGH)
   * @param Date boost::date Task Deadline
   *
   * @return optional<Task> created Task or nullopt in case one of the arguments is invalid.
   */
  static std::optional<Task>      create(const std::string& name, const std::string& label,
                                         Priority priority, const Date& duedate);

  std::string                     GetName() const;
  std::string                     GetLabel() const;
  Priority                        GetPriority() const;
  Date                            GetDate() const;


 private:
  std::string                     name_;
  std::string                     label_;
  Date                            due_date_;
  Priority                        priority_;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const Date &duedate);
};

#endif //TODOLIST__TASK_H_
