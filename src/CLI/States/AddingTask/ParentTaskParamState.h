//
// Created by rodion on 9/1/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_

#include <States/StateInterface.h>
#include <StateMachine.h>

class ParentTaskParamState : public StateInterface {
 public:
  StateResult     run(std::shared_ptr<Context> &context)            override;
  StateType       getType()                                         override;

 private:
  bool            input(const std::shared_ptr<IOInterface> &io_)    override;
  void            output(const std::shared_ptr<IOInterface> &io_)   override;

 private:
  unsigned int    param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
