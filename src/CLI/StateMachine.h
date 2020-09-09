//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATEMACHINE_H_

#include <memory>
#include <StateInterface.h>
#include <States/ExitState.h>
#include "Context/Context.h"
#include "StatesGraphType.h"

class StateMachine {
 public:
  static StateMachine                 create(const StatesGraphType&, std::shared_ptr<Context>&);

 public:
  bool                                execute();

 private:
  std::shared_ptr<StateInterface>     state_;
  std::shared_ptr<Context>            context_;
  std::shared_ptr<StateInterface>     start_state_;

 private:
  StateMachine(std::shared_ptr<StateInterface>&& start_state, std::shared_ptr<Context>& context);
};

#endif //TODOLIST_SRC_CLI_STATEMACHINE_H_
