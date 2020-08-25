//
// Created by rodion on 8/21/20.
//

#include "ViewTaskListState.h"

ViewTaskListState::ViewTaskListState() {
}

bool ViewTaskListState::input() {
  return true;
}

std::shared_ptr<StateInterface> ViewTaskListState::run() {
  return nullptr;
}

void ViewTaskListState::output() {
  std::cout << "[Output]: Tasks list view mode." << std::endl;
}
