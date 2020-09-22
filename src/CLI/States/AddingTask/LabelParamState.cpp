//
// Created by rodion on 8/27/20.
//

#include "LabelParamState.h"

StateResult LabelParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  this->input(context->io_);

  if(context->show_list_buffer_.checkBufferFullness() && context->show_list_buffer_.getByLabelFlag()) {
    context->show_list_buffer_.setLabel(this->param_);
    return StateResult::create(ErrorType::NO_ERRORS,
                               StateFactory::create(StateType::EXIT_STATE));
  }
  context->add_task_buffer_.setLabel(this->param_);
  return StateResult::create(ErrorType::NO_ERRORS,
                               StateFactory::create(StateType::ADD_TASK_PRIORITY_PARAM_STATE));
}

bool LabelParamState::input(const std::shared_ptr<IOInterface> &io_) {
  this->param_ = io_->input();
  return true;
}

void LabelParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter task label (not required): ");
}

StateType LabelParamState::getType() {
  return StateType::ADD_TASK_LABEL_PARAM_STATE;
}