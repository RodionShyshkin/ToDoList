//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CLI_COMMANDS_COMMANDPARSER_H_
#define TODOLIST_SRC_CLI_COMMANDS_COMMANDPARSER_H_

#include <map>
#include <string>
#include "Command.h"

namespace CommandParser {

  namespace CommandsMap {
    static std::map<std::string, Command> create() {
      std::map<std::string, Command> commands;
      commands["mainmenu"] = Command::MAINMENU;
      commands["mm"] = Command::MAINMENU;
      commands["add"] = Command::ADDTASK;
      commands["add_subtask"] = Command::ADDSUBTASK;
      commands["view"] = Command::GETTASK;
      commands["show"] = Command::GETTASKLIST;
      commands["remove"] = Command::REMOVETASK;
      commands["complete"] = Command::COMPLETETASK;
      commands["postpone"] = Command::POSTPONETASK;
      commands["save"] = Command::SAVETASKS;
      commands["load"] = Command::LOADTASKS;
      commands["exit"] = Command::EXIT;

      return commands;
    }
  }

  static Command Parse(std::string&& string) {
    auto command_map = CommandsMap::create();
    if(command_map.find(string) == command_map.end()) return Command::UNKNOWN;

    return command_map[string];
  }
}

#endif //TODOLIST_SRC_CLI_COMMANDS_COMMANDPARSER_H_
