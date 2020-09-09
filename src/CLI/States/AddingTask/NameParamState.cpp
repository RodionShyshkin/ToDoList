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

std::shared_ptr<StateInterface> NameParamState::run(std::unique_ptr<Context> &context) {
  input();
  output();
  if(!validateParam()) return nullptr;
  else {
//    context->name_ = param_;
//    context->updateContext(param_, context->getLabel(), context->getPriority(), context->getDate(), context->getParent());
    context->add_task_buffer_.setName(param_);
    return std::make_shared<LabelParamState>();
  return nullptr;
  }
}

void NameParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter name" << std::endl;
}

bool NameParamState::validateParam() const {
  if(param_.empty()) return false;
  if(parseCommand(param_) == Command::EXIT) return false;
  return true;
}

StateType NameParamState::getType() {
  return StateType::ADD_TASK_NAME_PARAM_STATE;
}