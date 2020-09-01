//
// Created by rodion on 9/1/20.
//

#include "ParentTaskParamState.h"
#include "NameParamState.h"

bool ParentTaskParamState::input() {
  this->param_ = 1;

  return true;
}

std::shared_ptr<AddTaskStateInterface> ParentTaskParamState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
  input();
  context->updateContext(context->getName(), context->getLabel(), context->getPriority(), context->getDate(),
                         this->param_);
  return std::make_shared<NameParamState>();
}

void ParentTaskParamState::output() {
  std::cout << "[Output]: AddTask state machine / Parent ID" << std::endl;
}
