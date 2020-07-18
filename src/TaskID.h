//
// Created by rodion on 7/18/20.
//

#ifndef TODOLIST_SRC_TASKID_H_
#define TODOLIST_SRC_TASKID_H_

#include <iostream>

class TaskID {
 public:
  TaskID();
  TaskID(const unsigned int &id);
  ~TaskID();

 public:
  friend std::ostream& operator<< (std::ostream &out, const TaskID &taskid);
  friend bool operator== (const TaskID &lhs, const TaskID rhs);

 private:
  unsigned int id_;
};

#endif //TODOLIST_SRC_TASKID_H_
