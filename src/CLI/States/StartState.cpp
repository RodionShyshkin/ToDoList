//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include "StartState.h"

StartState::StartState() {
  available_operations_.clear();
  available_operations_.insert(Command::ADDTASK);
  available_operations_.insert(Command::GETTASK);
  available_operations_.insert(Command::GETTASKLIST);
}

bool StartState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "view";
  operation_ = Operation::create(stringCommand);
  if(available_operations_.find(operation_->getCommandID()) == available_operations_.end()) return false;
  return true;
}

std::shared_ptr<StateInterface> StartState::run() {
  if(!input()) return nullptr;
  std::cout << operation_->getCommand() << std::endl;
  return operation_->getNextState();
}

void StartState::output() {
  std::cout << "[Output]: Main menu." << std::endl;
}
