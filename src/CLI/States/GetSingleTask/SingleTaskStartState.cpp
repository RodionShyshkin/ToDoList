//
// Created by rodion on 9/2/20.
//

#include <States/StateFactory.h>
#include "SingleTaskStartState.h"
#include "IDParamState.h"

bool SingleTaskStartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

std::shared_ptr<StateInterface> SingleTaskStartState::run(std::shared_ptr<Context> &context) {
  return StateFactory::create(StateType::SHOW_SINGLE_ID_PARAM_STATE);
}

void SingleTaskStartState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Show single task / Start");
}

StateType SingleTaskStartState::getType() {
  return StateType::SHOW_SINGLE_START_STATE;
}