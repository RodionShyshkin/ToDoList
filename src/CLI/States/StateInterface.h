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
#include "StateResult.h"
#include <IO/ConsoleIO.h>
#include <ErrorType.h>

//class StateResult;

class StateInterface {
 public:
  ~StateInterface()                                                                             = default;

 public:
  virtual StateResult                         run(std::shared_ptr<Context> &context)            = 0;
  virtual StateType                           getType()                                         = 0;

 private:
  virtual bool                                input(const std::shared_ptr<IOInterface> &io_)    = 0;
  virtual void                                output(const std::shared_ptr<IOInterface> &io_)   = 0;
};

#endif //TODOLIST_SRC_CLI_STATEINTERFACE_H_
