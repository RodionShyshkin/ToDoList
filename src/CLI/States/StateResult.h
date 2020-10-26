//
// Created by rodion on 9/20/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATERESULT_H_
#define TODOLIST_SRC_CLI_STATES_STATERESULT_H_

#include <memory>

/*
 * Represents the result of running some state.
 *
 * @see CommandStates/StateInterface.h
 * @see CommandStates/ErrorType.h
 *
 * @author Rodion Shyshkin
 */

enum class StateResult {
  SUCCESS,
  INCORRECT_INPUT,
  OPERATION_ERROR
};

#endif //TODOLIST_SRC_CLI_STATES_STATERESULT_H_
