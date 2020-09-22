//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_

#include <States/StateInterface.h>

class AddTaskStartState : public StateInterface {
 public:
  explicit AddTaskStartState(const bool& is_subtask);

  explicit AddTaskStartState(AddTaskStartState&) = default;

 public:
  StateResult run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

 private:
  bool                              is_subtask_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTARTSTATE_H_
