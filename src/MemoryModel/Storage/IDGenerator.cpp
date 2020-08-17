//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids_amount_(0) {}
IDGenerator::~IDGenerator() = default;


std::optional<TaskID> IDGenerator::GenerateID() {
  return TaskID::create(++ids_amount_);
}