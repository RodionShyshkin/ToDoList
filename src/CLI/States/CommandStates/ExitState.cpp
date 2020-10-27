//
// Created by rodion on 8/21/20.
//


#include "ExitState.h"

bool ExitState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult ExitState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  return StateResult::SUCCESS;
}

void ExitState::output(const std::shared_ptr<IOInterface> &io) {
  io->outputWithBreak("State machine finished.");
}

StateType ExitState::getType() const {
  return StateType::EXIT_STATE;
}

std::unique_ptr<StateInterface> ExitState::switchState() {
  return nullptr;
}