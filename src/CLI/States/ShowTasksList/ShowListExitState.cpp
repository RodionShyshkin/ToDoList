//
// Created by rodion on 8/28/20.
//

#include "ShowListExitState.h"

bool ShowListExitState::input() {
  return true;
}

std::shared_ptr<ShowListStateInterface> ShowListExitState::run(std::unique_ptr<ShowListContext> &context) {
  output();
  return std::shared_ptr<ShowListExitState>();
}

void ShowListExitState::output() {
  std::cout << "[Output]: ShowTasksList state machine / Exit" << std::endl;
}