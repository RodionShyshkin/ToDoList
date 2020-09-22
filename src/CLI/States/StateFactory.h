//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATEFACTORY_H_
#define TODOLIST_SRC_CLI_STATES_STATEFACTORY_H_

#include <CommandParser.h>
#include "StateInterface.h"

/*
 * Factory for states.
 *
 * @author Rodion Shyshkin
 */

class StateFactory {
 public:
  static std::shared_ptr<StateInterface>     create(const StateType&);
};

#endif //TODOLIST_SRC_CLI_STATES_STATEFACTORY_H_
