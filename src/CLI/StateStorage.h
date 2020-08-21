//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATESTORAGE_H_
#define TODOLIST_SRC_CLI_STATESTORAGE_H_

#include <memory>
#include <States/StateInterface.h>

class StateStorage {
 public:
  StateStorage();

  void execute();

 private:
  std::unique_ptr<StateInterface> state_;
};

#endif //TODOLIST_SRC_CLI_STATESTORAGE_H_
