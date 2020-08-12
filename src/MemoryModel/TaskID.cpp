//
// Created by rodion on 7/18/20.
//

#include "TaskID.h"

TaskID::TaskID() = default;

TaskID::TaskID(const unsigned int &id) {
  this->id_ = id;
}

unsigned int TaskID::GetID() const {
  return this->id_;
}

bool operator== (const TaskID& lhs, const TaskID& rhs) {
  return lhs.GetID() == rhs.GetID();
}

bool operator< (const TaskID& lhs, const TaskID& rhs) {
  return lhs.GetID() < rhs.GetID();
}
