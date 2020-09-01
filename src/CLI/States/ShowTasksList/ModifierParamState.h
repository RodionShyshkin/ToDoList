//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_

#include "ShowListStateInterface.h"

class ModifierParamState : public ShowListStateInterface {
 public:
  bool input() override;
  std::shared_ptr<ShowListStateInterface> run(std::unique_ptr<ShowListContext> &context) override;
  void output() override;

 private:
  ListModifier parseParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_MODIFIERPARAMSTATE_H_
