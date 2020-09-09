//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATEMACHINE_H_

#include <memory>
#include <StateInterface.h>
#include <States/ExitState.h>
#include "Context.h"
#include "StatesGraphType.h"

class StateMachine {
 public:
  static StateMachine                 create(const StatesGraphType&);

 public:
  bool                                execute();

 private:
  std::shared_ptr<StateInterface>     state_;
  std::unique_ptr<Context>            context_;
  std::shared_ptr<StateInterface>     start_state_;

 private:
  explicit StateMachine(std::shared_ptr<StateInterface>&& start_state);
};

#endif //TODOLIST_SRC_CLI_STATEMACHINE_H_
