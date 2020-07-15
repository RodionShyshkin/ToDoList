//
// Created by rodion on 7/15/20.
//

#ifndef TODOLIST__TASK_H_
#define TODOLIST__TASK_H_

#include <iostream>
//#include <ctime>

class Task {
 public:
  std::string getName() { return name; }
  std::string getLabel() { return label; }
  tm getDate() { return dueDate; }
  int getPriority() { return priority; }



/*  Priority getPriority() {

  }*/

 private:
  std::string name;
  std::string label;
  tm dueDate;
  enum Priority {
    LOW,
    MEDIUM,
    HIGH
  } priority;
};

#endif //TODOLIST__TASK_H_
