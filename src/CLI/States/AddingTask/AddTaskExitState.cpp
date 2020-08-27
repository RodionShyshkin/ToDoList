//
// Created by rodion on 8/27/20.
//

#include "AddTaskExitState.h"

bool AddTaskExitState::input() {
  return true;
}

std::shared_ptr<AddTaskStateInterface> AddTaskExitState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
  return std::shared_ptr<AddTaskExitState>();
}

void AddTaskExitState::output() {
  std::cout << "[Output]: AddTask state machine / Exit" << std::endl;
}