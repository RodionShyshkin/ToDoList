//
// Created by rodion on 9/20/20.
//

#include "StateResult.h"

StateResult StateResult::create(const ErrorType &type, const std::shared_ptr<StateInterface> &state) {
  if(type != ErrorType::NO_ERRORS && state != nullptr) throw std::invalid_argument("invalid StateResult");
  return StateResult{type, state};
}

StateResult::StateResult(const ErrorType &type, const std::shared_ptr<StateInterface> &state) {
  this->error_type_ = type;
  this->next_state_ = state;
}

ErrorType StateResult::getError() const {
  return this->error_type_;
}

std::shared_ptr<StateInterface> StateResult::getNextState() const {
  return this->next_state_;
}