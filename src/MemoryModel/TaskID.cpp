//
// Created by rodion on 7/18/20.
//

#include "TaskID.h"

TaskID::TaskID() = default;

TaskID::TaskID(const unsigned int &id) {
  this->id_ = id;
}

bool TaskID::operator== (TaskID id) const {
  return id.get_id() == this->get_id();
}

bool TaskID::operator== (unsigned int num) const {
  return this->get_id() == num;
}

bool TaskID::operator<(TaskID id) const {
  return this->get_id() < id.get_id();
}
