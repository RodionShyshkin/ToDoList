//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEMACHINE_H_

#include <memory>
#include "ShowListContext.h"
#include "ShowListStateInterface.h"

class ShowListStateMachine {
 public:
  ShowListStateMachine();

  bool execute();

 private:
  std::shared_ptr<ShowListStateInterface> state_;
  std::unique_ptr<ShowListContext> context_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEMACHINE_H_
