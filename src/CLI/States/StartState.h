//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_STARTSTATE_H_
#define TODOLIST_SRC_CLI_STARTSTATE_H_

#include <iostream>
#include <States/StateInterface.h>
#include "States/AddTaskState.h"

class StartState : public StateInterface {
 public:
  StartState() = default;
  StartState(Context k) {
    context_ = std::make_shared<Context>(k);
 //   context_ = k;
  }

 public:
  bool          input() override;
  bool          run() override;
  void          output() override;

 private:
  std::string   command_;
/*
 private:
  bool          validateCommand(const std::string&) override;*/
};

#endif //TODOLIST_SRC_CLI_STARTSTATE_H_
