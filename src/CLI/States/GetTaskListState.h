//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <ListModifier.h>

class GetTaskListState : public StateInterface {
 public:
  GetTaskListState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface> run() override;
  void output() override;

 private:
  ListModifier parseModifier(const std::string&);
  bool      parseFlag(const std::string&);

 private:
  ListModifier modifier_;
  bool is_sorted_;
};

#endif //TODOLIST_SRC_CLI_STATES_GETTASKLISTSTATE_H_
