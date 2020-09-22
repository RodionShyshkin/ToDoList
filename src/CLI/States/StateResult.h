//
// Created by rodion on 9/20/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATERESULT_H_
#define TODOLIST_SRC_CLI_STATES_STATERESULT_H_

#include <memory>
#include <ErrorType.h>

/*
 * Represents the result of running some state.
 *
 * @see States/StateInterface.h
 * @see States/ErrorType.h
 *
 * @author Rodion Shyshkin
 */

class StateInterface;

class StateResult {
 public:
  /*
   * Factory method for StateResult.
   *
   * @param ErrorType if operation has error and in the positive case which is this error.
   * @param std::shared_ptr<StateInterface> the next state if there are no errors.
   */
  static StateResult                create(const ErrorType&, const std::shared_ptr<StateInterface>&);

 public:
  ErrorType                         getError() const;
  std::shared_ptr<StateInterface>   getNextState() const;

 private:
  StateResult(const ErrorType&, const std::shared_ptr<StateInterface>&);

 private:
  ErrorType                         error_type_;
  std::shared_ptr<StateInterface>   next_state_;
};

#endif //TODOLIST_SRC_CLI_STATES_STATERESULT_H_
