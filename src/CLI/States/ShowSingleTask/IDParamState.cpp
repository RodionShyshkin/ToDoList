//
// Created by rodion on 9/2/20.
//

#include <States/ExitState.h>
#include "IDParamState.h"

bool IDParamState::input() {
  this->param_ = 1;
  return true;
}

std::shared_ptr<StateInterface> IDParamState::run(std::unique_ptr<Context> &context) {
  output();
  input();
  context->show_single_task_struct_.id_ = param_;
  return std::make_shared<ExitState>();
}

void IDParamState::output() {
  std::cout << "[Output]: Show single task / ID parameter" << std::endl;
}

StateType IDParamState::getType() {
  return StateType::SHOW_SINGLE_ID_PARAM_STATE;
}