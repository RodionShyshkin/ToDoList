//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
#define TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_

#include <optional>
#include "src/core/MemoryModel/Storage/Error.h"

/*
 * Class representing the result of adding tasks or subtasks.
 *
 * @author Rodion Shyshkin
 */

template <typename ErrorEnum>
class OperationResult {
 public:
  OperationResult(ErrorEnum err_code) : error_(err_code) {
    if(err_code == ErrorEnum::NO_ERRORS) {
      this->status_ = true;
    }
    else this->status_ = false;
  }

 public:
  bool                        GetStatus() const {return this->status_;}
  std::optional<ErrorEnum>    GetError() const {
    if(this->status_) return std::nullopt;
    return this->error_;
  }

 private:
  bool                        status_;
  ErrorEnum                   error_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
