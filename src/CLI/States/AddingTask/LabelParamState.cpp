//
// Created by rodion on 8/27/20.
//

#include <States/StateFactory.h>
#include "LabelParamState.h"

bool LabelParamState::input() {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> LabelParamState::run(std::shared_ptr<Context> &context) {
  this->output();
  if(!this->input()) return nullptr;
  if(!validateParam()) return StateFactory::create(this->getType());

  if(context->show_list_buffer_.checkBufferFullness()) context->show_list_buffer_.setLabel(this->param_);
  else context->add_task_buffer_.setLabel(this->param_);
  return StateFactory::create(StateType::ADD_TASK_PRIORITY_PARAM_STATE);
}

void LabelParamState::output() {
  ConsoleIO io;
  io.output("Enter task label (not required): ");
}

bool LabelParamState::validateParam() const {
  return true;
}

StateType LabelParamState::getType() {
  return StateType::ADD_TASK_LABEL_PARAM_STATE;
}