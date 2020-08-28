//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_

#include <States/StateInterface.h>
#include <Operation.h>

class ViewTaskState : public StateInterface {
 public:
  ViewTaskState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_
