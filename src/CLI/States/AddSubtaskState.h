//
// Created by rodion on 8/31/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_

#include <StateInterface.h>

class AddSubtaskState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::unique_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_
