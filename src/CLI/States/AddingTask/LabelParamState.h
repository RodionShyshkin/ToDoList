//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_

#include "AddTaskStateInterface.h"

class LabelParamState : public AddTaskStateInterface {
 public:
  bool input() override;
  std::shared_ptr<AddTaskStateInterface> run(std::unique_ptr<AddTaskContext> &context) override;
  void output() override;

 private:
  bool validateParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_LABELPARAMSTATE_H_
