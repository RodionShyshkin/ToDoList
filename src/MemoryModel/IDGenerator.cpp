//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids(0) {}
IDGenerator::~IDGenerator() = default;


TaskID IDGenerator::generateID() {
  return TaskID(++ids);
}