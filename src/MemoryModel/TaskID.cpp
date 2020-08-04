//
// Created by rodion on 7/18/20.
//

#include "TaskID.h"

TaskID::TaskID() = default;

TaskID::TaskID(const unsigned int &id) {
  this->id_ = id;
}


bool operator== (const TaskID &lhs, const TaskID &rhs) {
  return lhs.id_ == rhs.id_;
}

bool operator< (const TaskID& lhs, const TaskID& rhs) {
  return lhs.id_ < rhs.id_;
}