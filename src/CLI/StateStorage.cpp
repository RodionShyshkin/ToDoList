//
// Created by rodion on 8/21/20.
//

#include "StateStorage.h"
#include <States/StartState.h>
#include <iostream>

StateStorage::StateStorage() {
  state_ = std::make_shared<StartState>();
  context_ = std::make_unique<Context>();
}

void StateStorage::execute() {
  while(this->state_ != std::shared_ptr<ExitState>()) {
/*    if(this->state_ == nullptr) {
      std::cout << "ERROR" << std::endl;
      break;
    }*/
    this->state_ = std::move(state_->run(context_));
  }
}
