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
  std::string getName() const;
  std::string getLabel() const;
  Priority getPriority() const;
  int getDate() const;

  std::string convertPriority() const;

  void showTask() const;

//  friend std::ostream& operator<< (std::ostream &out, Task task);

 private:
  std::string name;
  std::string label;
  int dueDate;
  bool status;
  std::vector<Task> subtasks;
  Priority priority = EMPTY;
};

#endif //TODOLIST__TASK_H_
