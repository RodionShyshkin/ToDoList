//
// Created by rodion on 8/28/20.
//

#include "ShowListStartState.h"
#include "ModifierParamState.h"

bool ShowListStartState::input() {

  return true;
}

std::shared_ptr<StateInterface> ShowListStartState::run(std::unique_ptr<Context> &context) {
  output();
  return std::make_shared<ModifierParamState>();
}

void ShowListStartState::output() {
  std::cout << "[Output]: ShowTasksList state machine / Start" << std::endl;
}

StateType ShowListStartState::getType() {
  return StateType::SHOW_LIST_START_STATE;
}