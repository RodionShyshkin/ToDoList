//
// Created by rodion on 8/27/20.
//

#include "LabelParamState.h"

StateResult LabelParamState::run(std::shared_ptr<Context> context) {
  if(context->show_list_buffer_.checkBufferFullness() && !context->id_buffer_.checkBufferFullness())
    return StateResult::SUCCESS;

  output(context->io_);
  input(context->io_);

  if(!context->show_list_buffer_.checkBufferFullness() && context->show_list_buffer_.getByLabelFlag()) {
    context->show_list_buffer_.setLabel(param_);
    return StateResult::SUCCESS;
  }
  context->add_task_buffer_.setLabel(param_);
  return StateResult::SUCCESS;
}

bool LabelParamState::input(const std::shared_ptr<IOInterface> &io) {
  param_ = io->input();
  return true;
}

void LabelParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task label (not required): ");
}

StateType LabelParamState::getType() {
  return StateType::TASK_LABEL_PARAM;
}

std::unique_ptr<StateInterface> LabelParamState::switchState() {
  return nullptr;
}