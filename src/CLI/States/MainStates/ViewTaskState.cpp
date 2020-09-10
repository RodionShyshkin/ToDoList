//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskState.h"
#include "States/EditStates/RemoveTaskState.h"
#include "States/StateFactory.h"

bool ViewTaskState::input() {
  ConsoleIO io;
  this->command_ = parseCommand(io.inputCommand());

  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;

      //getting task
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
  }
  auto inputResult = this->input();
  if(!inputResult) return nullptr;
  this->output();
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Single task view mode.");
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}