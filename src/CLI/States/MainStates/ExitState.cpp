//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

ExitState::ExitState() {
}

bool ExitState::input() {
  return true;
}

std::shared_ptr<StateInterface>  ExitState::run(std::shared_ptr<Context> &context) {
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