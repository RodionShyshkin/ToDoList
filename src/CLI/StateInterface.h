//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATEINTERFACE_H_

#include <memory>
#include <set>
#include <Context/Context.h>
#include "CommandParser.h"
#include "StateType.h"

class StateInterface {
 public:
  ~StateInterface()                           = default;

 public:
  virtual bool                                input() = 0;
  virtual std::shared_ptr<StateInterface>     run(std::unique_ptr<Context> &context) = 0;
  virtual void                                output() = 0;
  virtual StateType                           getType() = 0;
};

#endif //TODOLIST_SRC_CLI_STATEINTERFACE_H_
