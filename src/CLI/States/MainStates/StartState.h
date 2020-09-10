//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_STARTSTATE_H_

#include <States/StateInterface.h>

class StartState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::shared_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;
};

#endif //TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
