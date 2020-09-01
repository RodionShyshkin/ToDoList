//
// Created by rodion on 8/21/20.
//

#include "StateStorage.h"
#include <States/StartState.h>
#include <iostream>
#include <States/ExitState.h>

StateStorage::StateStorage() {
  state_ = std::make_shared<StartState>();
  context_ = std::make_unique<Context>();
}

bool StateStorage::execute() {
  while(this->state_ != std::shared_ptr<ExitState>()) {
    if(this->state_ == nullptr) {
      std::cout << "ERROR" << std::endl;
      return false;
    }
    this->state_ = std::move(state_->run(context_));
  }
  return true;
}
