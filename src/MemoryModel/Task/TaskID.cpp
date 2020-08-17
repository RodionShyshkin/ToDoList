//
// Created by rodion on 7/18/20.
//

#include "TaskID.h"

TaskID::TaskID() = default;

TaskID::TaskID(const unsigned int &id) {
  this->id_ = id;
}

std::optional<TaskID> TaskID::create(const unsigned int &id) {
  if(id > 9999) return std::nullopt;
  return TaskID(id);
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
