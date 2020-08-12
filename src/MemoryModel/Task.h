//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include "MemoryModel/Date.h"
#include "MemoryModel/Priority.h"
#include <vector>
#include <memory>

class Task {
 public:
  Task();

 public:
  static Task                     create(const std::string& name, const std::string& label,
                                         Priority priority, const Date& duedate);

  std::string                     GetName() const;
  std::string                     GetLabel() const;
  Priority                        GetPriority() const;
  Date                            GetDate() const;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const Date &duedate);

 private:
  std::string                     name_;
  std::string                     label_;
  Date                            due_date_;
  Priority                        priority_;
};

#endif //TODOLIST__TASK_H_
