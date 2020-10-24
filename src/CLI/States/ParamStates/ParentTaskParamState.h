//
// Created by rodion on 9/1/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_

#include <States/StateInterface.h>

class ParentTaskParamState : public StateInterface {
 public:
  StateResult     run(std::shared_ptr<Context> context)            override;
  StateType       getType()                                        override;
  std::unique_ptr<StateInterface> switchState() override;

 private:
  bool            input(const std::shared_ptr<IOInterface> &io)    override;
  void            output(const std::shared_ptr<IOInterface> &io)   override;

 private:
  unsigned int    param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
