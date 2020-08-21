//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMMANDPARSER_H_
#define TODOLIST_SRC_CLI_STATES_COMMANDPARSER_H_

#include <iostream>

enum class Command {
  ADDTASK = 1,
  GETTASK,
  REMOVETASK,
  EXIT
};

Command parseCommand(const std::string&);

#endif //TODOLIST_SRC_CLI_STATES_COMMANDPARSER_H_
