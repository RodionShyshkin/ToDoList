//
// Created by rodion on 8/21/20.
//

#include <memory>
#include "CommandParser.h"

Command parseCommand(const std::string& command) {
  if(command == "add") return Command::ADDTASK;
  if(command == "add_subtask") return Command::ADDSUBTASK;
  if(command == "view") return Command::GETTASK;
  if(command == "show") return Command::GETTASKLIST;
  if(command == "remove") return Command::REMOVETASK;
  if(command == "postpone") return Command::POSTPONETASK;
  if(command == "complete") return Command::COMPLETETASK;
  if(command == "mm" || command == "mainmenu") return Command::MAINMENU;
  if(command == "exit") return Command::EXIT;
  return Command::UNKNOWN;
}

StateType getStateTypeByCommand(const Command& operation) {
  if(operation == Command::GETTASK) {
    return StateType::VIEW_TASK_STATE;
  }
  if(operation == Command::ADDTASK) {
    return StateType::ADD_TASK_STATE;
  }
  if(operation == Command::ADDSUBTASK) {
    return StateType::ADD_SUBTASK_STATE;
  }
  if(operation == Command::EXIT) {
    return StateType::EXIT_STATE;
  }
  if(operation == Command::REMOVETASK) {
    return StateType::REMOVE_TASK_STATE;
  }
  if(operation == Command::POSTPONETASK) {
    return StateType::POSTPONE_TASK_STATE;
  }
  if(operation == Command::COMPLETETASK) {
    return StateType::COMPLETE_TASK_STATE;
  }
  if(operation == Command::GETTASKLIST) {
    return StateType::VIEW_TASK_LIST_STATE;
  }
  if(operation == Command::MAINMENU) {
    return StateType::MAIN_MENU_STATE;
  }
  return StateType::UNKNOWN_STATE;
}
