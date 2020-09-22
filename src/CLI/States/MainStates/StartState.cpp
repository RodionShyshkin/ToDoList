//
// Created by rodion on 9/10/20.
//

#include "StartState.h"

bool StartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult StartState::run(std::shared_ptr<Context> &context) {
  return StateResult::create(
      ErrorType::NO_ERRORS,
      StateFactory::create(getStateTypeByCommand(Command::MAINMENU))
      );
}

void StartState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Start state.");
}

StateType StartState::getType() {
  return StateType::START_STATE;
}