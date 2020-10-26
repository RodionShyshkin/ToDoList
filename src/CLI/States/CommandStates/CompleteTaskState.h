//
// Created by rodion on 8/25/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_

#include <States/StateInterface.h>

class CompleteTaskState : public StateInterface {
 public:
  StateResult       run(std::shared_ptr<Context> context)             override;
  StateType         getType()                                         override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool              input(const std::shared_ptr<IOInterface> &io)    override;
  void              output(const std::shared_ptr<IOInterface> &io)   override;

 private:
  bool              task_list_flag_;
};

#endif //TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
