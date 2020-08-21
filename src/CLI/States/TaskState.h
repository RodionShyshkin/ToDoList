//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_TASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_TASKSTATE_H_

#include <States/StateInterface.h>

class TaskState : public StateInterface {
 public:
  bool input() override;
  std::unique_ptr<StateInterface> run() override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_TASKSTATE_H_
