//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATEMACHINE_H_

#include <memory>
#include <States/StateFactory.h>
#include "Context/Context.h"
#include "StatesMachineType.h"

class StateMachine {
 public:
  static StateMachine                 create(const StatesMachineType& type, std::shared_ptr<Context>& context);

 public:
  bool                                execute();

 private:
          std::shared_ptr<StateInterface>     state_;
          std::shared_ptr<Context>            context_;
  const   std::shared_ptr<StateInterface>     start_state_;

 private:
  StateMachine(std::shared_ptr<StateInterface>&& start_state, std::shared_ptr<Context>& context);
};

#endif //TODOLIST_SRC_CLI_STATEMACHINE_H_
