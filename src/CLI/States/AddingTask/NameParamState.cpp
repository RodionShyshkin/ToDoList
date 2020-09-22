//
// Created by rodion on 8/27/20.
//

#include <States/StateFactory.h>
#include "NameParamState.h"
#include "LabelParamState.h"


StateResult NameParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->add_task_buffer_.setName(this->param_);
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::ADD_TASK_LABEL_PARAM_STATE));
}

bool NameParamState::input(const std::shared_ptr<IOInterface> &io_) {
  this->param_ = io_->input();
  auto validated = NameParamState::validateParam(this->param_);
  return validated;
}

void NameParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter task name: ");
}

bool NameParamState::validateParam(const std::string& param) {
  if(param.empty()) return false;
  return true;
}

StateType NameParamState::getType() {
  return StateType::ADD_TASK_NAME_PARAM_STATE;
}