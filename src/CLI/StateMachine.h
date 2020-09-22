//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATEMACHINE_H_

#include <memory>
#include <States/StateFactory.h>
#include "Context/Context.h"
#include "StatesMachineType.h"

/*
 * Finite State Machine class, used to switch states, which change context.
 *
 * @see Context.h
 *
 * @author Rodion Shyshkin
 */

class StateMachine {
 public:
  /*
   * \brief Factory method for finite state machine.
   *
   * @param StateMachineType type of #{StateMachineType}
   * @param Context the state of the system
   *
   * @return StateMachine instance
   */
  static StateMachine                 create(const StatesMachineType& type, std::shared_ptr<Context>& context);

 public:
  /*
   * \brief Method which starts state machine.
   *
   * @return bool True if state machine's work does not have any fatal errors. False in another case.
   */
  bool                                execute();

 private:
          std::shared_ptr<StateInterface>     state_;
          std::shared_ptr<Context>            context_;
  const   std::shared_ptr<StateInterface>     start_state_;

 private:
  StateMachine(std::shared_ptr<StateInterface>&& start_state, std::shared_ptr<Context>& context);
};

#endif //TODOLIST_SRC_CLI_STATEMACHINE_H_
