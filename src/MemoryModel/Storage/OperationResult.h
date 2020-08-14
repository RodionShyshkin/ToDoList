//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
#define TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_

#include <optional>
#include "Error.h"

/*
 * Class representing the result of adding tasks or subtasks.
 *
 * @author Rodion Shyshkin
 */

class OperationResult {
 public:
  /*
   * Factory method for OperationResult.
   */
  static OperationResult    create(ErrorCode err_code);

 public:
  bool                      GetStatus() const;
  std::optional<ErrorCode>  GetError() const;

 private:
  OperationResult(ErrorCode err_code);

 private:
  bool                      status_;
  ErrorCode                 error_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
