//
// Created by rodion on 8/28/20.
//

#include "ShowListStateMachine.h"
#include "ShowListStartState.h"
#include "ShowListExitState.h"

ShowListStateMachine::ShowListStateMachine() {
  this->state_ = std::make_shared<ShowListStartState>();
  this->context_ = std::make_unique<ShowListContext>();
}

bool ShowListStateMachine::execute() {
  while(this->state_ != std::shared_ptr<ShowListExitState>()) {
    if(this->state_ == nullptr) {
      std::cout << "Error with getting tasks list!" << std::endl;
      return false;
    }
    this->state_ = std::move(this->state_->run(context_));
  }
  return true;
}