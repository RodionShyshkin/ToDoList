//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_STARTSTATE_H_

#include <States/StateInterface.h>
#include <Operation.h>

class StartState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run() override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
