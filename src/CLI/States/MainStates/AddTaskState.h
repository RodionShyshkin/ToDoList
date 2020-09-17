//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_


#include <States/StateInterface.h>

class AddTaskState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>     run(std::shared_ptr<Context> &context)    override;
  StateType                           getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDTASKSTATE_H_
