//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEMACHINE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEMACHINE_H_

#include <memory>
#include "AddTaskStateInterface.h"
#include "AddTaskContext.h"

class AddTaskStateMachine {
 public:
  AddTaskStateMachine();

  bool execute();

 private:
  std::shared_ptr<AddTaskStateInterface> state_;
  std::unique_ptr<AddTaskContext> context_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEMACHINE_H_
