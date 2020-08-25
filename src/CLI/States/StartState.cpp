//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include "StartState.h"

bool StartState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "view";
  operation_ = Operation::create(stringCommand);
  return true;
}

std::shared_ptr<StateInterface> StartState::run() {
  input();
  std::cout << operation_->getCommand() << std::endl;
  return operation_->getNextState();
}

void StartState::output() {
  std::cout << "[Output]: Main menu." << std::endl;
}
