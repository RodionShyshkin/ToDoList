//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_

#include <States/StateInterface.h>

class RemoveTaskState : public StateInterface {
 public:
  RemoveTaskState(const bool&);

 public:
  bool input() override;
  std::unique_ptr<StateInterface> run() override;
  void output() override;

 private:
  bool validateParams(const unsigned int& param);

 private:
  bool has_id;
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_REMOVETASKSTATE_H_
