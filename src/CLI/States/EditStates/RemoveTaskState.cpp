//
// Created by rodion on 8/21/20.
//


#include <StateMachine.h>
#include "RemoveTaskState.h"
#include "States/MainStates/MainMenuState.h"

bool RemoveTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  RemoveTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
  }
  this->task_id_ = context->id_buffer_.getID().value();

  this->output();

  context->id_buffer_.clearBuffer();
  if(context->show_list_buffer_.checkBufferFullness()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  context->show_list_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void RemoveTaskState::output() {
  ConsoleIO io;
  io.output("[Output]: Removes task.");
}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK_STATE;
}