//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_

#include <States/StateInterface.h>

class ModifierParamState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::unique_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  ListModifier parseParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
