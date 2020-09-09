//
// Created by rodion on 9/1/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_

#include <StateInterface.h>

class ParentTaskParamState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;

 private:
  unsigned int                      param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
