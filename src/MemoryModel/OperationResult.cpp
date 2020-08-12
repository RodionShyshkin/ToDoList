//
// Created by rodion on 8/10/20.
//

#include "OperationResult.h"

/*
 * Class representing the result of adding tasks or subtasks_.
 *
 * @author Rodion Shyshkin
 */

OperationResult::OperationResult(ErrorCode err_code) : error_(err_code) {
  if(err_code == ErrorCode::NO_ERRORS) {
    this->status_ = true;
  } else {
    this->status_ = false;
  }
}

OperationResult OperationResult::create(ErrorCode err_code) {
  return OperationResult(err_code);
}

bool OperationResult::GetStatus() const {
  return this->status_;
}

/*
 * @param [none]
 *
 * @see Error.h
 *
 * @return the Error instance if the status_ is false & nullopt if the status_ is true.
 */

std::optional<ErrorCode> OperationResult::GetError() const {
  if(this->status_) return std::nullopt;
  return this->error_;
}
