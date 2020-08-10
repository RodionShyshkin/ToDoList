//
// Created by rodion on 8/10/20.
//

#include "OperationResult.h"

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

bool OperationResult::get_status() const {
  return this->status_;
}

std::optional<Error> OperationResult::get_error() const {
  return this->error_;
}

Error OperationResult::create_error(Error::Code err_code) {
  return Error(err_code);
}