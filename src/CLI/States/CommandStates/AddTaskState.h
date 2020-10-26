//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_

#include <States/StateInterface.h>

class AddTaskState : public StateInterface {
 public:
  StateResult     run(std::shared_ptr<Context> context)           override;
  StateType       getType()                                       override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool            input(const std::shared_ptr<IOInterface> &io)  override;
  void            output(const std::shared_ptr<IOInterface> &io) override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
