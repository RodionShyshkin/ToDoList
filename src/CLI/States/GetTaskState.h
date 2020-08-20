//
// Created by rodion on 8/20/20.
//

#ifndef TODOLIST_SRC_CLI_GETTASKSTATE_H_
#define TODOLIST_SRC_CLI_GETTASKSTATE_H_

#include <States/StateInterface.h>
#include <States/RemoveTaskState.h>

class GetTaskState : public StateInterface {
 public:
  bool input() override;

  bool run() override;
  void output() override;

 private:
  std::string command_;
/*
 private:
  bool validateCommand(const std::string &) override;*/
};

#endif //TODOLIST_SRC_CLI_GETTASKSTATE_H_
