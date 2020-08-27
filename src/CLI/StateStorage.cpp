//
// Created by rodion on 8/21/20.
//

#include "StateStorage.h"
#include <States/StartState.h>
#include <iostream>

StateStorage::StateStorage() {
  std::unique_ptr<StateInterface> s = std::make_unique<StartState>();
  state_ = std::make_unique<StartState>();
}

void StateStorage::execute() {
  while(this->state_ != std::shared_ptr<ExitState>()) {
/*    if(this->state_ == nullptr) {
      std::cout << "ERROR" << std::endl;
      break;
    }*/
    this->state_ = std::move(state_->run());
  }
}
