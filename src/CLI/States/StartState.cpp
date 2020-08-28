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
  available_operations_.insert(Command::EXIT);

  std::random_device rd;
  std::mt19937 mersenne(rd());
  int m = mersenne();
}

bool StartState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  std::cout << "RUNS" << std::endl;
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 4;
  if(k == 0) stringCommand = "add";
  else if(k == 1) stringCommand = "view";
  else if(k == 2) stringCommand = "show";
  else stringCommand = "exit";
//  stringCommand = "add";

  operation_ = Operation::create(parseCommand(stringCommand));
  if(available_operations_.find(operation_->getCommand()) == available_operations_.end()) return false;
  return true;
}

std::shared_ptr<StateInterface> StartState::run(std::unique_ptr<Context> &context) {
  //std::cout << "RUNS" << std::endl;
  auto inputResult = input();
  if(!inputResult) return nullptr;
  output();
  return operation_->getNextState();
}

void StartState::output() {
  std::cout << "[Output]: Main menu." << std::endl;
}
