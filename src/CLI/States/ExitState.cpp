//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

ExitState::ExitState() {
  available_operations_.clear();
}

bool ExitState::input() {
  return true;
}

std::shared_ptr<StateInterface>  ExitState::run(std::unique_ptr<Context> &context) {
  input();
  output();
  return nullptr;
}

void ExitState::output() {
  std::cout << "[Output]: Finishes state machine.";
}

StateType ExitState::getType() {
  return StateType::EXIT_STATE;
}