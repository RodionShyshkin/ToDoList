//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_

#include <States/StateInterface.h>

class AddTaskStartState : public StateInterface {
 public:
  AddTaskStartState(const bool& is_subtask);

 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::unique_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  bool is_subtask_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
