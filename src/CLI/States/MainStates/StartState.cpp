//
// Created by rodion on 9/10/20.
//

#include <States/StateFactory.h>
#include "StartState.h"

bool StartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

std::shared_ptr<StateInterface> StartState::run(std::shared_ptr<Context> &context) {
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void StartState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Start state.");
}

StateType StartState::getType() {
  return StateType::START_STATE;
}