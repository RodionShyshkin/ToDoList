//
// Created by rodion on 8/27/20.
//

#include "PriorityParamState.h"

StateResult PriorityParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->add_task_buffer_.setPriority(this->param_);

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::ADD_TASK_DATE_PARAM_STATE));
}

bool PriorityParamState::input(const std::shared_ptr<IOInterface> &io_) {
  auto parsed = PriorityParamState::parseParam(io_->input());
  if(!parsed.has_value()) return false;
  this->param_ = parsed.value();
  return true;
}

void PriorityParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter task priority (not required) [Low, Medium, High]: ");
}

std::optional<Priority> PriorityParamState::parseParam(const std::string& param) {
  if(param.empty()) return Priority::EMPTY;
  else if(param == "Low") return Priority::LOW;
  else if(param == "Medium") return Priority::MEDIUM;
  else if(param == "High") return Priority::HIGH;
  else return std::nullopt;
}

StateType PriorityParamState::getType() {
  return StateType::ADD_TASK_PRIORITY_PARAM_STATE;
}