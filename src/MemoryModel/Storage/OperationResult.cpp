//
// Created by rodion on 8/10/20.
//

#include "OperationResult.h"

OperationResult::OperationResult(ErrorCode err_code) : error_(err_code) {
  if(err_code == ErrorCode::NO_ERRORS) {
    this->status_ = true;
  } else {
    this->status_ = false;
  }
}

bool OperationResult::GetStatus() const {
  return this->status_;
}

std::optional<ErrorCode> OperationResult::GetError() const {
  if(this->status_) return std::nullopt;
  return this->error_;
}
