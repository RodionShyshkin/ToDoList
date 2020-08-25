//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <Modifier.h>

class GetTaskListState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run() override;
  void output() override;

 private:
  Modifier parseModifier(const std::string&);
  bool      parseFlag(const std::string&);

 private:
  Modifier modifier_;
  bool is_sorted_;
};

#endif //TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_
