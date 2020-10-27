//
// Created by rodion on 10/24/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINE_H_

#include <queue>
#include <Context/Context.h>
#include <memory>
#include "States/StateType.h"

/*
 * \brief StateMachine which works with container of states,
 * which receive parameters and fill context by them.
 *
 * @see States/ParamStates
 *
 * @author Rodion Shyshkin
 */

class ParamStateMachine {
 public:
  static ParamStateMachine create(std::queue<StateType>&& states,
                                    std::shared_ptr<Context> context);

  void execute();

 private:
  ParamStateMachine(std::queue<StateType>&& states,
                      std::shared_ptr<Context> context);

 private:
  std::queue<StateType>    states_queue_;
  std::shared_ptr<Context> context_;
};

#endif //TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINE_H_
