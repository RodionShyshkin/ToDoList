//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEINTERFACE_H_

#include <memory>
#include <CommandParser.h>
#include <API/Priority.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include "AddTaskContext.h"

class Operation;

class AddTaskStateInterface {
 public:
  ~AddTaskStateInterface() = default;

 public:
  bool virtual              input() = 0;
  std::shared_ptr<AddTaskStateInterface> virtual              run(std::unique_ptr<AddTaskContext> &context) = 0;
  void virtual              output() = 0;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKSTATEINTERFACE_H_
