//
// Created by rodion on 8/27/20.
//

#include "AddTaskStateMachine.h"
#include "AddTaskStartState.h"
#include "AddTaskExitState.h"

AddTaskStateMachine::AddTaskStateMachine(const bool& is_subtask) {
  state_ = std::make_shared<AddTaskStartState>(is_subtask);
  context_ = std::make_unique<AddTaskContext>();
}

bool AddTaskStateMachine::execute() {
  while(this->state_ != std::shared_ptr<AddTaskExitState>()) {
    if(this->state_ == nullptr) return false;
    this->state_ = std::move(state_->run(context_));
  }
  return true;
}