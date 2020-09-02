//
// Created by rodion on 9/1/20.
//

#include "ParentTaskParamState.h"
#include "NameParamState.h"

bool ParentTaskParamState::input() {
  this->param_ = 1;

  return true;
}

std::shared_ptr<StateInterface> ParentTaskParamState::run(std::unique_ptr<Context> &context) {
  output();
  input();
  context->add_task_struct_.parent_id_ = param_;
  return std::make_shared<NameParamState>();
}

void ParentTaskParamState::output() {
  std::cout << "[Output]: AddTask state machine / Parent ID" << std::endl;
}

StateType ParentTaskParamState::getType() {
  return StateType::ADD_TASK_PARENT_PARAM_STATE;
}