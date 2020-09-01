//
// Created by rodion on 8/27/20.
//

#include "NameParamState.h"
#include "LabelParamState.h"

bool NameParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  srand(time(NULL));
  auto k = rand() % 4;
  stringParam = "Task Name";
  param_ = stringParam;
  return true;
}

std::shared_ptr<AddTaskStateInterface> NameParamState::run(std::unique_ptr<AddTaskContext> &context) {
  input();
  output();
  if(!validateParam()) return nullptr;
  else {
//    context->name_ = param_;
    context->updateContext(param_, context->getLabel(), context->getPriority(), context->getDate(), context->getParent());
    return std::make_shared<LabelParamState>();
  return nullptr;
  }
}

void NameParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter name" << std::endl;
}

bool NameParamState::validateParam() {
  if(param_.empty()) return false;
  if(parseCommand(param_) == Command::EXIT) return false;
  return true;
}