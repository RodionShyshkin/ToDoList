//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_

#include <States/StateInterface.h>

class SortedParamState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>   run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

  std::optional<bool>               parseParam()                              const;

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
