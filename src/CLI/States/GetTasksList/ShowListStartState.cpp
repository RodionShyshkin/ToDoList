//
// Created by rodion on 8/28/20.
//

#include <States/StateFactory.h>
#include "ShowListStartState.h"
#include "ModifierParamState.h"

bool ShowListStartState::input() {
  return true;
}

std::shared_ptr<StateInterface> ShowListStartState::run(std::shared_ptr<Context> &context) {
  this->output();
  return StateFactory::create(StateType::SHOW_LIST_MODIFIER_PARAM_STATE);
}

void ShowListStartState::output() {
  ConsoleIO io;
  io.output("[Output]: ShowTasksList state machine / Start");
}

StateType ShowListStartState::getType() {
  return StateType::SHOW_LIST_START_STATE;
}