//
// Created by rodion on 8/27/20.
//

#include <States/Validator.h>
#include "NameParamState.h"

StateResult NameParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->add_task_buffer_.setName(param_);
  return StateResult::SUCCESS;
}

bool NameParamState::input(const std::shared_ptr<IOInterface> &io) {
  param_ = io->input();
  auto validated = validator::ValidateName(param_);
  return validated;
}

void NameParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task name: ");
}

StateType NameParamState::getType() const {
  return StateType::TASK_NAME_PARAM;
}

std::unique_ptr<StateInterface> NameParamState::switchState() {
  return nullptr;
}
