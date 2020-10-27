//
// Created by rodion on 8/27/20.
//

#include <States/Validator.h>
#include "PriorityParamState.h"

StateResult PriorityParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->add_task_buffer_.setPriority(param_);

  return StateResult::SUCCESS;
}

bool PriorityParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = Validator::ParsePriority(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void PriorityParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task priority (not required) [Low, Medium, High]: ");
}

StateType PriorityParamState::getType() {
  return StateType::TASK_PRIORITY_PARAM;
}

std::unique_ptr<StateInterface> PriorityParamState::switchState() {
  return nullptr;
}