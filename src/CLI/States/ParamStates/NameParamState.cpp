//
// Created by rodion on 8/27/20.
//

#include "NameParamState.h"

StateResult NameParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->add_task_buffer_.setName(param_);
  return StateResult::SUCCESS;
}

bool NameParamState::input(const std::shared_ptr<IOInterface> &io) {
  param_ = io->input();
  auto validated = NameParamState::validateParam(param_);
  return validated;
}

void NameParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task name: ");
}

bool NameParamState::validateParam(const std::string& param) {
  if(param.empty()) return false;
  return true;
}

StateType NameParamState::getType() {
  return StateType::TASK_NAME_PARAM;
}

std::unique_ptr<StateInterface> NameParamState::switchState() {
  return nullptr;
}