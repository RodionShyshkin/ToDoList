//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_

#include "AddTaskStateInterface.h"

class PriorityParamState : public AddTaskStateInterface {
 public:
  bool input() override;
  std::shared_ptr<AddTaskStateInterface> run(std::unique_ptr<AddTaskContext> &context) override;
  void output() override;

 private:
  std::optional<Priority> parseParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_PRIORITYPARAMSTATE_H_
