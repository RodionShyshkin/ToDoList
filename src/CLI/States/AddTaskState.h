//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_ADDTASKSTATE_H_

#include "StateInterface.h"

class AddTaskState : public StateInterface {
 public:
  bool input() override;

  bool run() override;
  void output() override;

/* private:
  bool validateCommand(const std::string &) override;
 // void changeState() override;
*/
 private:
  std::string command_;
};

#endif //TODOLIST_SRC_CLI_ADDTASKSTATE_H_
