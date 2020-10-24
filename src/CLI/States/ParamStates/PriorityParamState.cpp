//
// Created by rodion on 8/27/20.
//

#include "PriorityParamState.h"

StateResult PriorityParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->add_task_buffer_.setPriority(param_);

  return StateResult::SUCCESS;
}

bool PriorityParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = PriorityParamState::parseParam(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void PriorityParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task priority (not required) [Low, Medium, High]: ");
}

std::optional<Priority> PriorityParamState::parseParam(const std::string& param) {
  if(param.empty()) return Priority::EMPTY;
  else if(param == "Low") return Priority::LOW;
  else if(param == "Medium") return Priority::MEDIUM;
  else if(param == "High") return Priority::HIGH;
  else return std::nullopt;
}

StateType PriorityParamState::getType() {
  return StateType::TASK_PRIORITY_PARAM;
}

std::unique_ptr<StateInterface> PriorityParamState::switchState() {
  return nullptr;
}