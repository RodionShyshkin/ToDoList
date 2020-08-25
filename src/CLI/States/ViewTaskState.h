//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_

#include <States/StateInterface.h>

class ViewTaskState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run() override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_