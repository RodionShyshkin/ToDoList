//
// Created by rodion on 9/9/20.
//

#include "AvailableCommands.h"

const std::map<StateType, std::set<Command>> AvailableCommands::available_commands_ = {
    {
        StateType::MAIN_MENU_STATE,
        {
            Command::ADDTASK,
            Command::GETTASKLIST,
            Command::EXIT
        }
    },

    {
        StateType::VIEW_TASK_LIST_STATE,
        {
            Command::GETTASK,
            Command::ADDSUBTASK,
            Command::COMPLETETASK,
            Command::POSTPONETASK,
            Command::REMOVETASK,
            Command::MAINMENU,
            Command::EXIT
        }
    },

    {
        StateType::VIEW_TASK_STATE,
        {
            Command::ADDSUBTASK,
            Command::COMPLETETASK,
            Command::POSTPONETASK,
            Command::REMOVETASK,
            Command::MAINMENU,
            Command::EXIT
        }
    }
};

std::set<Command> AvailableCommands::get(const StateType& type) {
  if(AvailableCommands::available_commands_.find(type) ==
  AvailableCommands::available_commands_.end())
    return std::set<Command>{};
  return AvailableCommands::available_commands_.at(type);
}

bool AvailableCommands::checkIsCommandAvailable(const StateType &type, const Command &command) {
  auto available_ = AvailableCommands::get(type);
  if(available_.find(command) == available_.end()) return false;
  return true;
}