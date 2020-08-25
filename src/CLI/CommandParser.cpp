//
// Created by rodion on 8/21/20.
//

#include "CommandParser.h"

Command parseCommand(const std::string& command) {
  if(command == "add") return Command::ADDTASK;
  if(command == "add_subtask") return Command::ADDSUBTASK;
  if(command == "view") return Command::GETTASK;
  if(command == "show") return Command::GETTASKLIST;
  if(command == "remove") return Command::REMOVETASK;
  if(command == "postpone") return Command::POSTPONETASK;
  if(command == "complete") return Command::COMPLETETASK;
  if(command == "exit") return Command::EXIT;
  return Command::UNKNOWN;
}
