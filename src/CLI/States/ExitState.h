//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_EXITSTATE_H_
#define TODOLIST_SRC_CLI_STATES_EXITSTATE_H_


#include <States/StateInterface.h>

class ExitState : public StateInterface {
 public:
  ExitState();

  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_EXITSTATE_H_
