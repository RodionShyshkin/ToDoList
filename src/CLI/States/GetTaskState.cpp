//
// Created by rodion on 8/20/20.
//

#include "GetTaskState.h"

bool GetTaskState::input() {
//  std::cout << "> ";
//  std::cin >> command_;
std::cout << "GTS";
//  if(!validateCommand(command_)) return false;
  return true;
}

bool GetTaskState::run() {
  if(command_ == "remove") {
    std::shared_ptr<StateInterface> k = std::make_shared<RemoveTaskState>();
    this->context_->changeState(k);
  }
  return true;
}

void GetTaskState::output() {
  std::cout << "GetTask State" << std::endl;
}
/*
bool GetTaskState::validateCommand(const std::string &com) {
  if(com == "remove") return true;
  return false;
}*/