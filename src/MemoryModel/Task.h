//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include "DueTime.h"
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
  Task(const std::string &name, const std::string &label, Priority priority, const DateTime &duetime);
  Task(const Task &task);
  ~Task();

 public:
  [[nodiscard]] std::string       getName() const;
  [[nodiscard]] std::string       getLabel() const;
  [[nodiscard]] Priority          getPriority() const;
  [[nodiscard]] DueTime           getDate() const;

 private:
  std::string                     name;
  std::string                     label;
  DueTime                         due_time;
  Priority                        priority;
};

#endif //TODOLIST__TASK_H_
