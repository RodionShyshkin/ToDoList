//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include <iostream>
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

  Task(const std::string &name, const std::string &label, Priority priority, const int &dueDate);

 public:
  std::string getName() const;
  std::string getLabel() const;
  Priority getPriority() const;
  int getDate() const;
  std::shared_ptr<Task> getRootTask() const;
  std::string getRootTaskName() const;
  std::vector<std::shared_ptr<Task>> getSubtasks() const;

  std::string convertPriority() const;

  void showTask() const;

 public:
  void pushSubtask(const Task &task);
  void setRoot(std::shared_ptr<Task> root);

 private:
  std::string name;
  std::string label;
  int dueDate;
  bool status;
  std::vector<std::shared_ptr<Task>> subtasks;
  Priority priority = EMPTY;
  std::shared_ptr<Task> rootTask;
};

#endif //TODOLIST__TASK_H_
