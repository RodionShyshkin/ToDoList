//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include "ViewTaskState.h"
#include "RemoveTaskState.h"
#include "StateFactory.h"

ViewTaskState::ViewTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::ADDSUBTASK);
  available_operations_.insert(Command::POSTPONETASK);
  available_operations_.insert(Command::REMOVETASK);
  available_operations_.insert(Command::COMPLETETASK);
  available_operations_.insert(Command::EXIT);
}

bool ViewTaskState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  //std::cout << "SDFSDFDF";
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 4;
  if(k == 0) stringCommand = "remove";
  else if(k == 1) stringCommand = "postpone";
  else if(k == 2) stringCommand = "complete";
  else stringCommand = "exit";
  stringCommand = "complete";

  command_ = parseCommand(stringCommand);
  if(available_operations_.find(this->command_) == available_operations_.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskState::run(std::unique_ptr<Context> &context) {
  auto machine_ = StateMachine::create(StatesGraphType::VIEW_SINGLE_TASK);
  if(machine_.execute()) {
    std::cout << "task got" << std::endl;
  }
  else {
    std::cout << "Error with getting task!" << std::endl;
  }
  input();
  std::cout << "ITS OK" << std::endl;
  return StateFactory::create(this->command_);
}

void ViewTaskState::output() {
  std::cout << "[Output]: Single task view mode." << std::endl;
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}