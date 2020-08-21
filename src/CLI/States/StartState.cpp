//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include "StartState.h"
#include "ExitState.h"
#include "AddTaskState.h"
#include "ViewTaskState.h"

bool StartState::input() {
  std::cout << "You can do following operations: ";


  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "view";
  command_ = parseCommand(stringCommand);
  return true;
}

std::unique_ptr<StateInterface> StartState::run() {
  input();
  if(command_ == Command::ADDTASK) {
    std::cout << "started" << std::endl;
    return std::make_unique<AddTaskState>();
  }
  else if(command_ == Command::GETTASK) {
    std::cout << "got" << std::endl;
    return std::make_unique<ViewTaskState>();
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
