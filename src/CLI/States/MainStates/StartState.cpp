//
// Created by rodion on 9/10/20.
//

#include <States/StateFactory.h>
#include "StartState.h"

bool StartState::input() {
  return true;
}

std::shared_ptr<StateInterface> StartState::run(std::shared_ptr<Context> &context) {
  output();
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void StartState::output() {
  std::cout << "[Output]: Start state." << std::endl;
}

StateType StartState::getType() {
  return StateType::START_STATE;
}