//
// Created by rodion on 8/25/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_

#include <States/StateInterface.h>
#include <StateMachine.h>

class CompleteTaskState : public StateInterface {
 public:
  StateResult       run(std::shared_ptr<Context> &context)            override;
  StateType         getType()                                         override;

 private:
  bool              input(const std::shared_ptr<IOInterface> &io_)    override;
  void              output(const std::shared_ptr<IOInterface> &io_)   override;

 private:
  unsigned int      task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_COMPLETETASKSTATE_H_
