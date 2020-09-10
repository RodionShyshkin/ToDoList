//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

bool ExitState::input() {
  return true;
}

std::shared_ptr<StateInterface>  ExitState::run(std::shared_ptr<Context> &context) {
  this->output();
  return nullptr;
}

void ExitState::output() {
  ConsoleIO io;
  io.output("[Output]: Finishes state machine.");
}

StateType ExitState::getType() {
  return StateType::EXIT_STATE;
}