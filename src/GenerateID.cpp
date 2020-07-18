//
// Created by rodion on 7/16/20.
//

#include "GenerateID.h"

GenerateID::GenerateID() : ids(0) {}
GenerateID::~GenerateID() = default;

TaskID GenerateID::generateID() {
  return TaskID(++ids);
}

std::ostream& operator<< (std::ostream& out, const GenerateID& taskid) {
  out << taskid.ids;
  return out;
}

bool operator==(const GenerateID& lhs, const GenerateID& rhs) {
  return (lhs.ids == rhs.ids);
}

