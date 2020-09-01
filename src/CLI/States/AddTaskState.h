//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_


#include <States/StateInterface.h>
#include "boost/date_time/gregorian/gregorian.hpp"

class AddTaskState : public StateInterface {
 public:
  AddTaskState();

  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;

 private:

};

#endif //TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
