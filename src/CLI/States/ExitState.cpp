//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

bool ExitState::input() {
  this->operation_ = Operation::create("exit");
  return true;
}

std::shared_ptr<StateInterface> ExitState::run() {
  std::cout << "Exit" << std::endl;
  return nullptr;
}

void ExitState::output() {
  std::cout << "Exit";
}