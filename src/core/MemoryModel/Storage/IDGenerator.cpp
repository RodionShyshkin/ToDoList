//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids_amount_(0) {}

std::optional<TaskID> IDGenerator::GenerateID() {
  return TaskID(++ids_amount_);
}