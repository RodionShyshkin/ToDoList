//
// Created by rodion on 9/10/20.
//

#include <States/StateFactory.h>
#include "StartState.h"

bool StartState::input() {
  return true;
}

std::shared_ptr<StateInterface> StartState::run(std::shared_ptr<Context> &context) {
  this->output();
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void StartState::output() {
  ConsoleIO io;
  io.output("[Output]: Start state.");
}

StateType StartState::getType() {
  return StateType::START_STATE;
}