//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_

#include <States/StateInterface.h>

class GetTaskState : public StateInterface {
 public:
  bool input() override;
  std::unique_ptr<StateInterface> run() override;
  void output() override;

 private:
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_
