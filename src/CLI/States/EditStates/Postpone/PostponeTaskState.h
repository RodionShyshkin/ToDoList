//
// Created by rodion on 8/25/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_POSTPONETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_POSTPONETASKSTATE_H_

#include <States/StateInterface.h>

class PostponeTaskState : public StateInterface {
 public:
  PostponeTaskState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::shared_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;
};

#endif //TODOLIST_SRC_CLI_STATES_POSTPONETASKSTATE_H_