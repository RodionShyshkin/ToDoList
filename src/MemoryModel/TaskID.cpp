//
// Created by rodion on 7/18/20.
//

#include "TaskID.h"

TaskID::TaskID() = default;
TaskID::~TaskID() = default;

TaskID::TaskID(const unsigned int &id) {
  this->id_ = id;
}


std::ostream& operator<< (std::ostream &out, const TaskID &taskid) {
 out << taskid.id_;
 return out;
}
bool operator== (const TaskID &lhs, const TaskID &rhs) {
  return lhs.id_ == rhs.id_;
}
