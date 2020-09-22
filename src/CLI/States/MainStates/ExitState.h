//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_EXITSTATE_H_
#define TODOLIST_SRC_CLI_STATES_EXITSTATE_H_


#include <States/StateInterface.h>

class ExitState : public StateInterface {
 public:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  StateResult run(std::shared_ptr<Context> &context)    override;
  void output(const std::shared_ptr<IOInterface> &io_) override;
  StateType                         getType()                                 override;
};

#endif //TODOLIST_SRC_CLI_STATES_EXITSTATE_H_
