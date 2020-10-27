//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CLI_COMMANDS_AVAILABLECOMMANDS_H_
#define TODOLIST_SRC_CLI_COMMANDS_AVAILABLECOMMANDS_H_

#include <States/StateType.h>
#include <set>
#include <map>
#include "Command.h"


namespace available_commands {

  namespace available_commands_map {
    static std::map<StateType, std::set<Command>> create() {
      return {
          {
              StateType::MAIN_MENU,
              {
                  Command::ADDTASK,
                  Command::GETTASKLIST,
                  Command::SAVETASKS,
                  Command::LOADTASKS,
                  Command::EXIT
              }
          },

          {
              StateType::SHOW_TASKS_LIST,
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
              StateType::SHOW_TASK,
              {
                  Command::ADDSUBTASK,
                  Command::COMPLETETASK,
                  Command::POSTPONETASK,
                  Command::REMOVETASK,
                  Command::GETTASKLIST,
                  Command::MAINMENU,
                  Command::EXIT
              }
          }
      };
    }
  }

  static bool IsCommandAvailable(const StateType& state_type, const Command& command) {
    auto commands_map = available_commands_map::create();
    if(commands_map.find(state_type) == commands_map.end()) return false;

    auto commands_set = commands_map[state_type];
    if(commands_set.find(command) == commands_set.end()) return false;
    return true;
  }
}

#endif //TODOLIST_SRC_CLI_COMMANDS_AVAILABLECOMMANDS_H_
