//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_


#include <States/StateInterface.h>

class GetTaskState : public StateInterface {
 public:
  GetTaskState();

  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;

 private:
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_GETTASKSTATE_H_
