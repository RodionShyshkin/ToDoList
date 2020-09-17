//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <random>

class ViewTaskListState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)            override;
  StateType                         getType()                                         override;

 private:
  bool                              input(const std::shared_ptr<IOInterface> &io_)    override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

  static void                       showList(const std::vector<TaskDTO>&);

 private:
  Command command_;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
