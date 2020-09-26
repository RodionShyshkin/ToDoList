//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_AVAILABLECOMMANDS_H_
#define TODOLIST_SRC_CLI_AVAILABLECOMMANDS_H_

#include <map>
#include <set>
#include "States/StateType.h"
#include "CommandParser.h"

class AvailableCommands {
 public:
  static bool              checkIsCommandAvailable(const StateType&, const Command&);

 private:
  static std::set<Command> get(const StateType&);

 private:
  static const std::map<StateType, std::set<Command>> available_commands_;
};


#endif //TODOLIST_SRC_CLI_AVAILABLECOMMANDS_H_
