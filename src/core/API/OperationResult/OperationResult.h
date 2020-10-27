//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
#define TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_

#include <optional>

/*
 * Class representing the result of some operations.
 *
 * @author Rodion Shyshkin
 */

template <typename ErrorEnum>
class OperationResult {
 public:
  static OperationResult      Success() {
    return OperationResult{std::nullopt};
  }

  static OperationResult      Fail(const ErrorEnum& err_code) {
    return OperationResult{err_code};
  }

 public:
  std::optional<ErrorEnum>    GetError() const { return error_; }

 private:
  OperationResult(const std::optional<ErrorEnum>& err_code) : error_(err_code) {  }

 private:
  std::optional<ErrorEnum>    error_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
