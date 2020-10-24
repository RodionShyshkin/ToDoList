//
// Created by rodion on 10/23/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMMANDSTATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATES_COMMANDSTATEMACHINE_H_

#include <memory>
#include "States/StateType.h"
#include "States/StateInterface.h"

class CommandStateMachine {
 public:
  static CommandStateMachine create(const StateType& start_state,
                                    std::shared_ptr<Context>&& context);

  void execute();

 private:
  CommandStateMachine(const StateType& start_state,
                      std::shared_ptr<Context>&& context);

 private:
  std::unique_ptr<StateInterface> state_;
  std::shared_ptr<Context> context_;
};

#endif //TODOLIST_SRC_CLI_STATES_COMMANDSTATEMACHINE_H_
