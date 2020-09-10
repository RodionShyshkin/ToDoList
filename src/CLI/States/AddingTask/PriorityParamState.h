//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_

#include <States/StateInterface.h>

class PriorityParamState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;

 private:
  std::optional<Priority>           parseParam()                              const;

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
