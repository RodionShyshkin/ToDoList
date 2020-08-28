//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTARTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTARTSTATE_H_

#include "ShowListStateInterface.h"

class ShowListStartState : public ShowListStateInterface {
 public:
  bool input() override;
  std::shared_ptr<ShowListStateInterface> run(std::unique_ptr<ShowListContext> &context) override;
  void output() override;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTARTSTATE_H_
