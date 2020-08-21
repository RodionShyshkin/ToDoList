//
// Created by rodion on 8/21/20.
//

#include "TaskListState.h"

bool TaskListState::input() {
  return true;
}

std::unique_ptr<StateInterface> TaskListState::run() {
  return nullptr;
}

void TaskListState::output() {

}
