//
// Created by rodion on 8/25/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_

#include <States/StateInterface.h>

class CompleteTaskState : public StateInterface {
 public:
  CompleteTaskState(std::optional<unsigned int> task_id);

 public:
  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;

 private:
  bool validateParams(const unsigned int& param);

 private:
  bool has_id_;
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
