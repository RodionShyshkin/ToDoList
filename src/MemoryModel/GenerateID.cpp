//
// Created by rodion on 7/16/20.
//

#include "GenerateID.h"

GenerateID::GenerateID() : ids(0) {}
GenerateID::~GenerateID() = default;


TaskID GenerateID::generateID() {
  return TaskID(++ids);
}