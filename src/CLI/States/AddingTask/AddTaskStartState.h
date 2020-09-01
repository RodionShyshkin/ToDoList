//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_

#include "AddTaskStateInterface.h"

class AddTaskStartState : public AddTaskStateInterface {
 public:
  AddTaskStartState(const bool& is_subtask);

 public:
  bool input() override;
  std::shared_ptr<AddTaskStateInterface> run(std::unique_ptr<AddTaskContext> &context) override;
  void output() override;

 private:
  bool is_subtask_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
