//
// Created by rodion on 9/2/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_

#include <States/StateInterface.h>

class SingleTaskStartState : public StateInterface {
 public:
  StateResult run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_
