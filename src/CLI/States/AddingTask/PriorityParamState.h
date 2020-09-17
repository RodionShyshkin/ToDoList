//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_

#include <States/StateInterface.h>

class PriorityParamState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

  std::optional<Priority>           parseParam()                              const;

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
