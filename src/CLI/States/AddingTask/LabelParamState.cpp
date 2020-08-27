//
// Created by rodion on 8/27/20.
//

#include "LabelParamState.h"
#include "PriorityParamState.h"

bool LabelParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  srand(time(NULL));
  auto k = rand() % 4;
  stringParam = "";
  param_ = stringParam;
  return true;
}

std::shared_ptr<AddTaskStateInterface> LabelParamState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
  input();
  if(!validateParam()) return nullptr;
  else {
//    context->label_ = param_;
    context->updateContext(context->getName(), param_, context->getPriority(), context->getDate());
    return std::make_shared<PriorityParamState>();
  }
}

void LabelParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter label" << std::endl;
}

bool LabelParamState::validateParam() const {
  if(parseCommand(param_) == Command::EXIT) return false;
  return true;
}