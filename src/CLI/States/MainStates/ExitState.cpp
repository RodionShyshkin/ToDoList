//
// Created by rodion on 8/21/20.
//


#include "ExitState.h"

bool ExitState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult ExitState::run(std::shared_ptr<Context> &context) {
  return StateResult::create(
      ErrorType::NO_ERRORS,
      nullptr
      );
}

void ExitState::output(const std::shared_ptr<IOInterface> &io_) { }

StateType ExitState::getType() {
  return StateType::EXIT_STATE;
}