//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include <iostream>
#include <vector>

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
  std::string getName();
  std::string getLabel();
  std::string getPriority();
  int getDate();

 private:
  std::string name;
  std::string label;
  int dueDate;
  bool status;
  std::vector<Task> subtasks;
  Priority priority = EMPTY;
};

#endif //TODOLIST__TASK_H_
