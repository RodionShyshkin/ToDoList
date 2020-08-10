//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
#define TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_

#include <iostream>
#include <optional>
#include "MemoryModel/Error.h"

class OperationResult {
 public:
  OperationResult(std::optional<Error> error);

 public:
  bool                    get_status() const;
  std::optional<Error>    get_error() const;

 private:
  bool                    status_;
  std::optional<Error>    error_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_OPERATIONRESULT_H_
