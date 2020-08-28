//
// Created by rodion on 8/21/20.
//


#include <iostream>
#include "ExitState.h"

ExitState::ExitState() {
  available_operations_.clear();
}

bool ExitState::input() {
  this->operation_ = Operation::create(parseCommand("exit"));
  return true;
}

std::shared_ptr<StateInterface>  ExitState::run(std::unique_ptr<Context> &context) {
  input();
  output();
  return std::shared_ptr<ExitState>();
}

void ExitState::output() {
  std::cout << "[Output]: Finishes program.";
}