//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include "MemoryModel/DateTime.h"
#include <vector>
#include <memory>

class Task {
 public:
  enum Priority {
    EMPTY,
    LOW,
    MEDIUM,
    HIGH
  };

 public:
  Task();
  Task(const std::string &name, const std::string &label, Priority priority, const DateTime &duedate);
  Task(const Task &task);

 public:
  std::string                     getName() const;
  std::string                     getLabel() const;
  Priority                        getPriority() const;
  DateTime                        getDate() const;

 private:
  std::string                     name;
  std::string                     label;
  DateTime                        due_date;
  Priority                        priority;
};

#endif //TODOLIST__TASK_H_
