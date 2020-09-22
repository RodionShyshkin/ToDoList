//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_

#include <States/StateInterface.h>

class ModifierParamState : public StateInterface {
 public:
  StateResult           run(std::shared_ptr<Context> &context)            override;
  StateType             getType()                                         override;

 private:
  bool                  input(const std::shared_ptr<IOInterface> &io_)    override;
  void                  output(const std::shared_ptr<IOInterface> &io_)   override;

  static ListModifier   parseParam(const std::string&);

 private:
  ListModifier          param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
