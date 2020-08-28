//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEINTERFACE_H_

#include <memory>
#include <CommandParser.h>
#include <API/Priority.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include "ShowListContext.h"

class Operation;

class ShowListStateInterface {
 public:
  ~ShowListStateInterface() = default;

 public:
  bool virtual              input() = 0;
  std::shared_ptr<ShowListStateInterface> virtual              run(std::unique_ptr<ShowListContext> &context) = 0;
  void virtual              output() = 0;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTSTATEINTERFACE_H_
