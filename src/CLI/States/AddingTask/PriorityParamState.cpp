//
// Created by rodion on 8/27/20.
//

#include <States/StateFactory.h>
#include "PriorityParamState.h"
#include "DateParamState.h"

bool PriorityParamState::input() {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> PriorityParamState::run(std::shared_ptr<Context> &context) {
  this->output();
  if(!this->input()) return nullptr;
  auto param = this->parseParam();
  if(!param.has_value()) return nullptr;

  context->add_task_buffer_.setPriority(param.value());
  return StateFactory::create(StateType::ADD_TASK_DATE_PARAM_STATE);
}

void PriorityParamState::output() {
  ConsoleIO io;
  io.output("Enter task priority (not required) [Low, Medium, High]: ");
}

std::optional<Priority> PriorityParamState::parseParam() const {
  if(param_.empty()) return Priority::EMPTY;
  else if(param_ == "Low") return Priority::LOW;
  else if(param_ == "Medium") return Priority::MEDIUM;
  else if(param_ == "High") return Priority::HIGH;
  else return std::nullopt;
}

StateType PriorityParamState::getType() {
  return StateType::ADD_TASK_PRIORITY_PARAM_STATE;
}