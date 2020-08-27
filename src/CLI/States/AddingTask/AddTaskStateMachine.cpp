//
// Created by rodion on 8/27/20.
//

#include "AddTaskStateMachine.h"
#include "AddTaskStartState.h"
#include "AddTaskExitState.h"

AddTaskStateMachine::AddTaskStateMachine() {
  state_ = std::make_shared<AddTaskStartState>();
  context_ = std::make_unique<AddTaskContext>();
}

bool AddTaskStateMachine::execute() {
  while(this->state_ != std::shared_ptr<AddTaskExitState>()) {
    if(this->state_ == nullptr) return false;
    this->state_ = std::move(state_->run(context_));
  }
  return true;
}