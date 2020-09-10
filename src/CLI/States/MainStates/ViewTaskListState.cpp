//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskListState.h"
#include "States/StateFactory.h"

bool ViewTaskListState::input() {
  ConsoleIO io;
  this->command_ = parseCommand(io.input());

  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskListState::run(std::shared_ptr<Context> &context) {
  if(!context->show_list_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_TASKS_LIST, context);
    if (machine_.execute()) {
      std::cout << "task list got" << std::endl;
    } else {
      std::cout << "Error with getting tasks list!" << std::endl;
    }
  }
  if(!this->input()) return nullptr;

  this->output();
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskListState::output() {
  ConsoleIO io;
  io.output("[Output]: Tasks list view mode.");
}

StateType ViewTaskListState::getType() {
  return StateType::VIEW_TASK_LIST_STATE;
}