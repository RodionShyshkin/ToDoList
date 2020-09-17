//
// Created by rodion on 8/27/20.
//

#include <States/StateFactory.h>
#include "NameParamState.h"
#include "LabelParamState.h"

bool NameParamState::input(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> NameParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return nullptr;
  if(!this->validateParam()) return StateFactory::create(this->getType());

  context->add_task_buffer_.setName(param_);
  return StateFactory::create(StateType::ADD_TASK_LABEL_PARAM_STATE);
}

void NameParamState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.output("Enter task name: ");
}

bool NameParamState::validateParam() const {
  if(param_.empty()) return false;
  return true;
}

StateType NameParamState::getType() {
  return StateType::ADD_TASK_NAME_PARAM_STATE;
}