//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_

#include <StateInterface.h>

class LabelParamState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;

 private:
  bool                              validateParam()                           const;

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
