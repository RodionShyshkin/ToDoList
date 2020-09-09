//
// Created by rodion on 9/9/20.
//

#include "AvailableCommands.h"

const std::map<StateType, std::set<Command>> AvailableCommands::available_commands_ = {
    {
        StateType::START_STATE,
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