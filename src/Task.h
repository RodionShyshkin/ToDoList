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
  Task(const std::string &name, const std::string &label, Priority priority, const DueTime &dueDate);
  Task(const Task &task);
  ~Task();

 public:
  std::string getName() const;
  std::string getLabel() const;
  bool getStatus() const;
  Priority getPriority() const;
  DueTime getDate() const;

 public:
  void setStatus();

 public:
  std::string showPriority() const;
  void showTask() const;

 private:
  std::string name;
  std::string label;
  DueTime dueDate;
  bool status;
  Priority priority = EMPTY;
};

#endif //TODOLIST__TASK_H_
