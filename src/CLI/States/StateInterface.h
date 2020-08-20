//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATEINTERFACE_H_

#include "Context.h"
#include <memory>

class StateInterface {
 public:
  ~StateInterface() = default;

 public:
  bool virtual              input() = 0;
  bool virtual              run() = 0;
  void virtual              output() = 0;
/*
 private:
  bool virtual              validateCommand(const std::string&) = 0;*/

 protected:
  std::shared_ptr<Context>  context_;
};

#endif //TODOLIST_SRC_CLI_STATEINTERFACE_H_
