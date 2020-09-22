//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_

#include <States/StateInterface.h>

class NameParamState : public StateInterface {
 public:
  StateResult run(std::shared_ptr<Context> &context)    override;
  StateType                         getType()                                 override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

  static bool                              validateParam(const std::string&);

 private:
  std::string                       param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_
