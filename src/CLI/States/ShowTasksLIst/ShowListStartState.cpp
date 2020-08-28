//
// Created by rodion on 8/28/20.
//

#include "ShowListStartState.h"
#include "ModifierParamState.h"

bool ShowListStartState::input() {

  return true;
}

std::shared_ptr<ShowListStateInterface> ShowListStartState::run(std::unique_ptr<ShowListContext> &context) {
  output();
  return std::make_shared<ModifierParamState>();
}

void ShowListStartState::output() {
  std::cout << "[Output]: ShowTasksList state machine / Start" << std::endl;
}