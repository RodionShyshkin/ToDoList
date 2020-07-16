//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include "DueTime.h"
#include "TaskID.h"
#include <vector>
#include <memory>

enum Priority {
  EMPTY,
  LOW,
  MEDIUM,
  HIGH
};

class Task {
 public:
  Task();

  Task(const std::string &name, const std::string &label, Priority priority, const DueTime &dueDate);

  Task(const Task &task);

  ~Task();

 public:
  unsigned int getId() const;
  std::string getName() const;
  std::string getLabel() const;
  bool getStatus() const;
  Priority getPriority() const;
  DueTime getDate() const;
  std::shared_ptr<Task> getRootTask() const;
  std::string getRootTaskName() const;
  std::vector<std::shared_ptr<Task>> getSubtasks() const;

 public:
  void setStatus();
  void setRoot(std::shared_ptr<Task> root);

 public:
  std::string convertPriority() const;
  void showTask() const;
  void pushSubtask(const Task &task);

 private:
  unsigned int id;
  std::string name;
  std::string label;
  DueTime dueDate;
  bool status;
  std::vector<std::shared_ptr<Task>> subtasks;
  Priority priority = EMPTY;
  std::shared_ptr<Task> rootTask;
};

#endif //TODOLIST__TASK_H_
