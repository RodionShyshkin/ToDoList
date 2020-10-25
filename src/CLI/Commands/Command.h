//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CLI_COMMANDS_COMMAND_H_
#define TODOLIST_SRC_CLI_COMMANDS_COMMAND_H_

enum class Command {
  UNKNOWN,
  ADDTASK,
  ADDSUBTASK,
  GETTASK,
  GETTASKLIST,
  REMOVETASK,
  POSTPONETASK,
  COMPLETETASK,
  MAINMENU,
  SAVETASKS,
  LOADTASKS,
  EXIT
};

#endif //TODOLIST_SRC_CLI_COMMANDS_COMMAND_H_