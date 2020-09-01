//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_

#include "ShowListStateInterface.h"

class SortedParamState : public ShowListStateInterface {
 public:
  bool input() override;
  std::shared_ptr<ShowListStateInterface> run(std::unique_ptr<ShowListContext> &context) override;
  void output() override;

 private:
  std::optional<bool> parseParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SORTEDPARAMSTATE_H_
