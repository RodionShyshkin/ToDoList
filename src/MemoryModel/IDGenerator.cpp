//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids_amount_(0) {}
IDGenerator::~IDGenerator() = default;


TaskID IDGenerator::GenerateID() {
  return TaskID(++ids_amount_);
}