//
// Created by rodion on 9/2/20.
//

#include <States/MainStates/ExitState.h>
#include <States/StateFactory.h>
#include "IDParamState.h"

bool IDParamState::input() {
  ConsoleIO io;
  try {
    this->param_ = std::stoi(io.input());
  }
  catch(const std::invalid_argument&) {
    return false;
  }
  catch(const std::out_of_range&) {
    return false;
  }
  return true;
}

std::shared_ptr<StateInterface> IDParamState::run(std::shared_ptr<Context> &context) {
  this->output();
  if(!this->input()) return nullptr;

  //context->show_single_task_struct_.id_ = param_;

  context->id_buffer_.setID(param_);
  return StateFactory::create(StateType::EXIT_STATE);
}

void IDParamState::output() {
  ConsoleIO io;
  io.output("Enter task ID: ");
}

StateType IDParamState::getType() {
  return StateType::SHOW_SINGLE_ID_PARAM_STATE;
}