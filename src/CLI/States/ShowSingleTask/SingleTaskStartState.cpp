//
// Created by rodion on 9/2/20.
//

#include "SingleTaskStartState.h"
#include "IDParamState.h"

bool SingleTaskStartState::input() {
  return true;
}

std::shared_ptr<StateInterface> SingleTaskStartState::run(std::unique_ptr<Context> &context) {
  output();
  return std::make_shared<IDParamState>();
}

void SingleTaskStartState::output() {
  std::cout << "[Output]: Show single task / Start" << std::endl;
}

StateType SingleTaskStartState::getType() {
  return StateType::SHOW_SINGLE_START_STATE;
}