//
// Created by rodion on 9/20/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATERESULT_H_
#define TODOLIST_SRC_CLI_STATES_STATERESULT_H_

#include <memory>
//#include <States/StateInterface.h>
#include <ErrorType.h>

class StateInterface;

class StateResult {
 public:
  static StateResult create(const ErrorType&, const std::shared_ptr<StateInterface>&);

 public:
  ErrorType getError() const;
  std::shared_ptr<StateInterface> getNextState() const;

 private:
  StateResult(const ErrorType&, const std::shared_ptr<StateInterface>&);

 private:
  ErrorType error_type_;
  std::shared_ptr<StateInterface> next_state_;
};

#endif //TODOLIST_SRC_CLI_STATES_STATERESULT_H_
