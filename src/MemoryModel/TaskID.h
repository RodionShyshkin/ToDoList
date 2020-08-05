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

 public:
  unsigned int get_id() const {
    return this->id_;
  }

 public:
  bool operator== (TaskID id) const;
  bool operator== (unsigned int num) const;
  bool operator< (TaskID id) const;

 private:
  unsigned int      id_;
};

#endif //TODOLIST_SRC_TASKID_H_
