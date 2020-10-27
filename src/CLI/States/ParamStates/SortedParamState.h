//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_

#include <States/StateInterface.h>

class SortedParamState : public StateInterface {
 public:
  StateResult                   run(std::shared_ptr<Context> context)          override;
  StateType                     getType() const                                override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool                          input(const std::shared_ptr<IOInterface> &io)  override;
  void                          output(const std::shared_ptr<IOInterface> &io) override;

 private:
  bool                          param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
