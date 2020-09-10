//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_


#include <States/StateInterface.h>

class RemoveTaskState : public StateInterface {
 public:
  RemoveTaskState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface>  run(std::shared_ptr<Context> &context) override;
  void output() override;

  StateType getType() override;

 private:
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
