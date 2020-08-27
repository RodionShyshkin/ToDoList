//
// Created by rodion on 8/26/20.
//

#include "AddTaskStartState.h"
#include "NameParamState.h"

bool AddTaskStartState::input() {

  return true;
}

std::shared_ptr<AddTaskStateInterface> AddTaskStartState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
//  return nullptr;
  return std::make_shared<NameParamState>();
}

void AddTaskStartState::output() {
  std::cout << "[Output]: AddTask state machine / Start State" << std::endl;
}