//
// Created by rodion on 8/27/20.
//

#include <States/Validator.h>
#include "DateParamState.h"

StateResult DateParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  if(context->add_task_buffer_.checkBufferFullness())
    context->add_task_buffer_.setDate(param_);
  else
    context->postpone_buffer_.setNewDate(param_);

  return StateResult::SUCCESS;
}

bool DateParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = validator::ParseDate(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void DateParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter deadline: ");
}

StateType DateParamState::getType() {
  return StateType::TASK_DATE_PARAM;
}

std::unique_ptr<StateInterface> DateParamState::switchState() {
  return nullptr;
}