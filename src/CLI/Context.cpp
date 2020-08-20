//
// Created by rodion on 8/19/20.
//

#include <States/StartState.h>
#include "Context.h"

Context::Context() {
  this->state_ = std::make_shared<StartState>(StartState(*this));
}

void Context::changeState(std::shared_ptr<StateInterface>& newstate) {
  this->state_ = newstate;
  state_->output();
}


void Context::readState() {
  state_->output();
}

void Context::execute() {
  state_->input();
  state_->run();
  state_->output();
}

void Context::printState() {

}