//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_

#include <States/StateInterface.h>

class LabelParamState : public StateInterface {
 public:
  StateResult     run(std::shared_ptr<Context> context)            override;
  StateType       getType()                                        override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool            input(const std::shared_ptr<IOInterface> &io)    override;
  void            output(const std::shared_ptr<IOInterface> &io)   override;

 private:
  std::string     param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
