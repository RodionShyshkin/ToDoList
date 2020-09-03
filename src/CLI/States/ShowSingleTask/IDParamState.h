//
// Created by rodion on 9/2/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_

#include <StateInterface.h>

class IDParamState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::unique_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;

 private:
  unsigned int param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_IDPARAMSTATE_H_
