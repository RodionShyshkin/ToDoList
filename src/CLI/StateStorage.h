//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATESTORAGE_H_
#define TODOLIST_SRC_CLI_STATESTORAGE_H_

#include <memory>
#include <States/StateInterface.h>
#include "Context.h"

class StateStorage {
 public:
  StateStorage();

  bool execute();

 private:
  std::shared_ptr<StateInterface> state_;
  std::unique_ptr<Context> context_;
};

#endif //TODOLIST_SRC_CLI_STATESTORAGE_H_
