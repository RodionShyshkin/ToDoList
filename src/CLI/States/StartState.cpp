//
// Created by rodion on 8/19/20.
//

#include "StartState.h"

bool StartState::input() {
//  std::cout << "> ";
 // std::cin >> command_;
 command_ = "add";
  //if(!validateCommand(command_)) return false;
  return true;
}

bool StartState::run() {
  if(command_ == "add") {
    std::shared_ptr<StateInterface> k = std::make_shared<AddTaskState>();
    this->context_->changeState(k);
    return true;
  }
  return false;
}

void StartState::output() {
  std::cout << "Start State" << std::endl;
}
/*
bool StartState::validateCommand(const std::string &com) {
  if(com == "add") return true;
  return false;
}*/
