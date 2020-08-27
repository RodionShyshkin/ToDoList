//
// Created by rodion on 8/27/20.
//

#include "PriorityParamState.h"
#include "DateParamState.h"

bool PriorityParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  srand(time(NULL));
  auto k = rand() % 4;
  stringParam = "";
  param_ = stringParam;
  return true;
}

std::shared_ptr<AddTaskStateInterface> PriorityParamState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
  input();
  auto param = parseParam();
  if(!param.has_value()) return nullptr;
  else {
//    context->priority_ = param.value();
    context->updateContext(context->getName(), context->getLabel(), param.value(), context->getDate());
    return std::make_shared<DateParamState>();
  }
}

void PriorityParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter priority" << std::endl;
}

std::optional<Priority> PriorityParamState::parseParam() const {
  if(param_.empty()) return Priority::EMPTY;
  else if(param_ == "Low") return Priority::LOW;
  else if(param_ == "Medium") return Priority::MEDIUM;
  else if(param_ == "High") return Priority::HIGH;
  else return std::nullopt;
}