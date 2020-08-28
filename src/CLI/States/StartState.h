//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_STARTSTATE_H_

#include <States/StateInterface.h>
#include <Operation.h>
#include <random>

class StartState : public StateInterface {
 public:
  StartState();

  bool input() override;
  std::shared_ptr<StateInterface>  run(std::unique_ptr<Context> &context) override;
  void output() override;

 private:
  std::mt19937 mersenne;
};

#endif //TODOLIST_SRC_CLI_STATES_STARTSTATE_H_
