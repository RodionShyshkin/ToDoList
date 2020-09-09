//
// Created by rodion on 9/2/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_

#include <StateInterface.h>

class SingleTaskStartState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWSINGLETASK_SINGLETASKSTARTSTATE_H_
