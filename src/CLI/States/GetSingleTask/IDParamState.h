//
// Created by rodion on 9/2/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_

#include <States/StateInterface.h>

class IDParamState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

 private:
  unsigned int param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_
