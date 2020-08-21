//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include "StartState.h"
#include "ExitState.h"
#include "AddTaskState.h"

bool StartState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "add";
  command_ = parseCommand(stringCommand);
  return true;
}



std::unique_ptr<StateInterface> StartState::run() {
  input();
  if(command_ == Command::ADDTASK) {
    std::cout << "started" << std::endl;
    return std::make_unique<AddTaskState>();
  }
  else if(command_ == Command::EXIT) {
    std::cout << "exited" << std::endl;
    return std::make_unique<ExitState>();
  }
  return nullptr;
}



void StartState::output() {
  std::cout << "S";
}
