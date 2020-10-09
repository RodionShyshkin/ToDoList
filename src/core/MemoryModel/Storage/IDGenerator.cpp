//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids_amount_(0) {}

TaskID IDGenerator::GenerateID() {
  return TaskID{++this->ids_amount_};
}