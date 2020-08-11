//
// Created by rodion on 8/10/20.
//

#include "OperationResult.h"

/*
 * Class representing the result of adding tasks or subtasks.
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

bool OperationResult::get_status() const {
  return this->status_;
}

/*
 * @param [none]
 *
 * @see Error.h
 *
 * @return the Error instance if the status is false & nullopt if the status is true.
 */

std::optional<ErrorCode> OperationResult::get_error() const {
  if(this->status_) return std::nullopt;
  return this->error_;
}
