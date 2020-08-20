//
// Created by rodion on 8/20/20.
//

#include "RemoveTaskState.h"

bool RemoveTaskState::input() {
  //std::cout << "> ";
//  std::cin >> command_;
std::cout << "RTS";
  //if(!validateCommand(command_)) return false;
  return true;
}

bool RemoveTaskState::run() {
  std::cout << "Removed" << std::endl;
  std::shared_ptr<StateInterface> k = std::make_shared<StartState>();
  this->context_->changeState(k);
  return true;
}


void RemoveTaskState::output() {
  std::cout << "Remove State" << std::endl;
}
/*
bool RemoveTaskState::validateCommand(const std::string &com) {
  return false;
}*/