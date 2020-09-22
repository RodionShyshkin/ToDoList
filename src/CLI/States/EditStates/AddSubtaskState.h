//
// Created by rodion on 8/31/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_

#include <States/StateInterface.h>
#include <StateMachine.h>

class AddSubtaskState : public StateInterface {
 public:
  StateResult       run(std::shared_ptr<Context> &context)           override;
  StateType         getType()                                        override;

 private:
  bool              input(const std::shared_ptr<IOInterface> &io_)   override;
  void              output(const std::shared_ptr<IOInterface> &io_)  override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDSUBTASKSTATE_H_
