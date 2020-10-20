//
// Created by rodion on 8/21/20.
//

#include "CommandParser.h"

Command parseCommand(const std::string& command) {
  if(command == "add") return Command::ADDTASK;
  else if(command == "add_subtask") return Command::ADDSUBTASK;
  else if(command == "view") return Command::GETTASK;
  else if(command == "show") return Command::GETTASKLIST;
  else if(command == "remove") return Command::REMOVETASK;
  else if(command == "postpone") return Command::POSTPONETASK;
  else if(command == "complete") return Command::COMPLETETASK;
  else if(command == "mm" || command == "mainmenu") return Command::MAINMENU;
  else if(command == "save") return Command::SAVETASKS;
  else if(command == "load") return Command::LOADTASKS;
  else if(command == "exit") return Command::EXIT;
  else return Command::UNKNOWN;
}

StateType getStateTypeByCommand(const Command& operation) {
  if(Command::GETTASK == operation) {
    return StateType::VIEW_TASK_STATE;
  }
  else if(Command::ADDTASK == operation) {
    return StateType::ADD_TASK_STATE;
  }
  else if(Command::ADDSUBTASK == operation) {
    return StateType::ADD_SUBTASK_STATE;
  }
  else if(Command::EXIT == operation) {
    return StateType::EXIT_STATE;
  }
  else if(Command::REMOVETASK == operation) {
    return StateType::REMOVE_TASK_STATE;
  }
  else if(Command::POSTPONETASK == operation) {
    return StateType::POSTPONE_TASK_STATE;
  }
  else if(Command::COMPLETETASK == operation) {
    return StateType::COMPLETE_TASK_STATE;
  }
  else if(Command::GETTASKLIST == operation) {
    return StateType::VIEW_TASK_LIST_STATE;
  }
  else if(Command::MAINMENU == operation) {
    return StateType::MAIN_MENU_STATE;
  }
  else if(Command::SAVETASKS == operation) {
    return StateType::SAVE_TASKS_STATE;
  }
  else if(Command::LOADTASKS == operation) {
    return StateType::LOAD_TASKS_STATE;
  }
  return StateType::UNKNOWN_STATE;
}
