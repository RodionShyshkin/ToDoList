//
// Created by rodion on 7/16/20.
//

#include "IDGenerator.h"

IDGenerator::IDGenerator() : ids_amount_(0) {}

std::optional<TaskID> IDGenerator::GenerateID() {
  auto id = TaskID{++this->ids_amount_};
  if(this->ids_amount_ == 10000) return std::nullopt;
  return id;
}