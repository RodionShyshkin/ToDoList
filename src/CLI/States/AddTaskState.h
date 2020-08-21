//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_

#include <States/StateInterface.h>
#include "boost/date_time/gregorian/gregorian.hpp"

class AddTaskState : public StateInterface {
 public:
  bool input() override;
  std::unique_ptr<StateInterface> run() override;
  void output() override;

 private:
  void parseParameters(const std::string&);

 private:
  std::string task_name_;
  std::string task_label_;
  std::string task_priority_;
  std::string task_deadline_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
