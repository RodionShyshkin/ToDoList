//
// Created by rodion on 8/21/20.
//

#include "CommandParser.h"

Command parseCommand(const std::string& command) {
  if(command == "add") return Command::ADDTASK;
  if(command == "view") return Command::GETTASK;
  if(command == "remove") return Command::REMOVETASK;
  if(command == "exit") return Command::EXIT;
}
