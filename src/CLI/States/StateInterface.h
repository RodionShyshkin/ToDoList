//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATEINTERFACE_H_

#include <memory>
#include <set>
#include <Context.h>
#include "CommandParser.h"

class Operation;

class StateInterface {
 public:
  ~StateInterface() = default;

 public:
  bool virtual              input() = 0;
  std::shared_ptr<StateInterface> virtual run(std::unique_ptr<Context> &context) = 0;
  void virtual              output() = 0;

/*
 private:
  bool virtual              validateCommand(const std::string&) = 0;*/

 protected:
  std::shared_ptr<Operation> operation_;
  std::set<Command> available_operations_;
};

#endif //TODOLIST_SRC_CLI_STATEINTERFACE_H_
