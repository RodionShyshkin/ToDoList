//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKEXITSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKEXITSTATE_H_

#include "AddTaskStateInterface.h"

class AddTaskExitState : public AddTaskStateInterface {
 public:
  bool input() override;
  std::shared_ptr<AddTaskStateInterface> run(std::unique_ptr<AddTaskContext> &context) override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKEXITSTATE_H_
