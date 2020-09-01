//
// Created by rodion on 9/1/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_

#include "AddTaskStateInterface.h"

class ParentTaskParamState : public AddTaskStateInterface {
 public:
  bool input() override;
  std::shared_ptr<AddTaskStateInterface> run(std::unique_ptr<AddTaskContext> &context) override;
  void output() override;

 private:
  unsigned int param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PARENTTASKPARAMSTATE_H_
