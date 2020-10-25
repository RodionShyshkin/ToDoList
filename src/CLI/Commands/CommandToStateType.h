//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMMANDTOSTATETYPE_H_
#define TODOLIST_SRC_CLI_STATES_COMMANDTOSTATETYPE_H_

#include <Commands/Command.h>
#include <States/StateType.h>
#include <map>

namespace CommandToStateType {
  namespace CommandStateMap {
    static std::map<Command, StateType> create() {
      std::map<Command, StateType> states;

      states[Command::MAINMENU] = StateType::MAIN_MENU;
      states[Command::ADDTASK] = StateType::ADD_TASK;
      states[Command::ADDSUBTASK] = StateType::ADD_SUBTASK;
      states[Command::GETTASK] = StateType::SHOW_TASK;
      states[Command::GETTASKLIST] = StateType::SHOW_TASKS_LIST;
      states[Command::REMOVETASK] = StateType::REMOVE_TASK;
      states[Command::COMPLETETASK] = StateType::COMPLETE_TASK;
      states[Command::POSTPONETASK] = StateType::POSTPONE_TASK;
      states[Command::SAVETASKS] = StateType::SAVE_TASKS;
      states[Command::LOADTASKS] = StateType::LOAD_TASKS;
      states[Command::EXIT] = StateType::EXIT_STATE;

      return states;
    }
  }

  static StateType Convert(const Command& command) {
    auto command_states_map = CommandStateMap::create();
    if(command_states_map.find(command) == command_states_map.end()) return StateType::UNKNOWN_STATE;

    return command_states_map[command];
  }
}

#endif //TODOLIST_SRC_CLI_STATES_COMMANDTOSTATETYPE_H_
