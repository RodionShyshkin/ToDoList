//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_


#include <States/StateInterface.h>

class RemoveTaskState : public StateInterface {
 public:
  RemoveTaskState(std::optional<unsigned int> task_id);

 public:
  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;

  StateType getType() override;

 private:
  bool validateParams(const unsigned int& param);

 private:
  bool has_id_;
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
