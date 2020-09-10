//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <random>

class ViewTaskListState : public StateInterface {
 public:
  ViewTaskListState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface>  run(std::shared_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  Command command_;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_