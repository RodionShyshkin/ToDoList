//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

bool ExitState::input() {
  return true;
}

std::shared_ptr<StateInterface>  ExitState::run(std::shared_ptr<Context> &context) {
  return nullptr;
}

void ExitState::output() { }

StateType ExitState::getType() {
  return StateType::EXIT_STATE;
}