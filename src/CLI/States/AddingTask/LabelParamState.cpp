//
// Created by rodion on 8/27/20.
//

#include "LabelParamState.h"
#include "PriorityParamState.h"

bool LabelParamState::input() {
  std::string stringParam;
  stringParam = "";
  param_ = stringParam;
  return true;
}

std::shared_ptr<StateInterface> LabelParamState::run(std::shared_ptr<Context> &context) {
  output();
  input();
  if(!validateParam()) return nullptr;
  else {
//    context->label_ = param_;
//    context->updateContext(context->getName(), param_, context->getPriority(), context->getDate(), context->getParent());
    context->add_task_buffer_.setLabel(param_);
    return std::make_shared<PriorityParamState>();
  }
}

void LabelParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter label" << std::endl;
}

bool LabelParamState::validateParam() const {
  if(parseCommand(param_) == Command::EXIT) return false;
  return true;
}

StateType LabelParamState::getType() {
  return StateType::ADD_TASK_LABEL_PARAM_STATE;
}