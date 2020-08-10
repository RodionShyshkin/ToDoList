//
// Created by rodion on 8/10/20.
//

#include "OperationResult.h"

/*
 * Class representing the result of adding tasks or subtasks.
 *
 * @author Rodion Shyshkin
 */

OperationResult::OperationResult(std::optional<Error> error) {
  if(error.has_value()) {
    this->status_ = false;
    this->error_ = error;
  }
  else {
    this->status_ = true;
    this->error_ = std::nullopt;
  }
}

/*
 * @param [none]
 *
 * @return the status of an operation, true or false
 */

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

std::optional<Error> OperationResult::get_error() const {
  return this->error_;
}

/*
 * Generates Error instance by the code of an error.
 *
 * @param Error::Code code of the error
 *
 * @return Error instance
 */

Error OperationResult::create_error(Error::Code err_code) {
  return Error(err_code);
}