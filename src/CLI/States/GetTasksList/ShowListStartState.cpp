//
// Created by rodion on 8/28/20.
//

#include <States/StateFactory.h>
#include <States/StateResult.h>
#include "ShowListStartState.h"
#include "ModifierParamState.h"

bool ShowListStartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult ShowListStartState::run(std::shared_ptr<Context> &context) {
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::SHOW_LIST_MODIFIER_PARAM_STATE));
}

void ShowListStartState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: ShowTasksList state machine / Start");
}

StateType ShowListStartState::getType() {
  return StateType::SHOW_LIST_START_STATE;
}