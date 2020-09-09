//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_

#include <StateInterface.h>

class SortedParamState : public StateInterface {
 public:
  bool                              input()                                   override;
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  void                              output()                                  override;
  StateType                         getType()                                 override;

 private:
  std::optional<bool>               parseParam()                              const;

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
