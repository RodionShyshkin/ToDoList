//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_


#include <StateInterface.h>

class AddTaskState : public StateInterface {
 public:
  AddTaskState();

  bool                                input()                                   override;
  std::shared_ptr<StateInterface>     run(std::shared_ptr<Context> &context)    override;
  void                                output()                                  override;
  StateType                           getType()                                 override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
