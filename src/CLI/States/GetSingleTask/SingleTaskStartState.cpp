//
// Created by rodion on 9/2/20.
//

#include <States/StateFactory.h>
#include "SingleTaskStartState.h"
#include "IDParamState.h"

bool SingleTaskStartState::input() {
  return true;
}

std::shared_ptr<StateInterface> SingleTaskStartState::run(std::shared_ptr<Context> &context) {
  this->output();
  return StateFactory::create(StateType::SHOW_SINGLE_ID_PARAM_STATE);
}

void SingleTaskStartState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Show single task / Start");
}

StateType SingleTaskStartState::getType() {
  return StateType::SHOW_SINGLE_START_STATE;
}