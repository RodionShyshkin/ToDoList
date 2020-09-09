//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include <AvailableCommands.h>
#include "StartState.h"

StartState::StartState() {
}

bool StartState::input() {
  std::string stringCommand;

  std::cout << "RUNS" << std::endl;
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 3;
  if(k == 0) stringCommand = "add";
  else if(k == 1) stringCommand = "show";
  else stringCommand = "exit";
//  stringCommand = "show";

  this->command_ = parseCommand(stringCommand);
  auto available = AvailableCommands::get(this->getType());

  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface> StartState::run(std::shared_ptr<Context> &context) {
  auto inputResult = input();
  if(!inputResult) return nullptr;
  output();
  std::cout << "WORKS" << std::endl;
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void StartState::output() {
  std::cout << "[Output]: Main menu." << std::endl;
}

StateType StartState::getType() {
  return StateType::START_STATE;
}