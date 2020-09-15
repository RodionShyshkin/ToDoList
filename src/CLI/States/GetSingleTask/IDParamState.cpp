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
  if(!context->show_list_buffer_.checkBufferFullness()) return nullptr;
  this->output();
  if(!this->input()) return nullptr;

  auto list = context->show_list_buffer_.getList();
  if(this->param_ >= list.size()) return nullptr;

  context->id_buffer_.setID(list[this->param_].getID());
  return StateFactory::create(StateType::EXIT_STATE);
}

void IDParamState::output() {
  ConsoleIO io;
  io.output("Enter task ID: ");
}

StateType IDParamState::getType() {
  return StateType::SHOW_SINGLE_ID_PARAM_STATE;
}