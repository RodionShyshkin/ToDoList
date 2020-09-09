//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskState.h"
#include "RemoveTaskState.h"
#include "StateFactory.h"

ViewTaskState::ViewTaskState() {
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
//  stringCommand = "remove";

  this->command_ = parseCommand(stringCommand);
  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskState::run(std::unique_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;

      //getting task
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
  }
  auto inputResult = input();
  if(!inputResult) return nullptr;
  output();
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskState::output() {
  std::cout << "[Output]: Single task view mode." << std::endl;
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}