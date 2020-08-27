//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <ListModifier.h>

class ViewTaskListState : public StateInterface {
 public:
  ViewTaskListState();

 public:
  bool input() override;
  std::shared_ptr<StateInterface> run() override;
  void output() override;

 private:
  ListModifier modifier_;
  bool is_sorted_;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
