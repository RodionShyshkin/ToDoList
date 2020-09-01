//
// Created by rodion on 8/21/20.
//

#include <States/ShowTasksList/ShowListStateMachine.h>
#include "ViewTaskListState.h"
#include "StateFactory.h"

ViewTaskListState::ViewTaskListState() {
  available_operations_.clear();
  available_operations_.insert(Command::ADDSUBTASK);
  available_operations_.insert(Command::POSTPONETASK);
  available_operations_.insert(Command::REMOVETASK);
  available_operations_.insert(Command::COMPLETETASK);
  available_operations_.insert(Command::EXIT);
}

bool ViewTaskListState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 4;
  if(k == 0) stringCommand = "remove";
  else if(k == 1) stringCommand = "postpone";
  else if(k == 2) stringCommand = "complete";
  else stringCommand = "exit";
//  stringCommand = "complete";

  this->command_ = parseCommand(stringCommand);
  if(available_operations_.find(this->command_) == available_operations_.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskListState::run(std::unique_ptr<Context> &context) {
  ShowListStateMachine machine_;
  if(machine_.execute()) {
    std::cout << "task list got" << std::endl;
  }
  else {
    std::cout << "Error with getting tasks list!" << std::endl;
  }
  input();
  output();
  return StateFactory::create(this->command_);
}

void ViewTaskListState::output() {
  std::cout << "[Output]: Tasks list view mode." << std::endl;
}
