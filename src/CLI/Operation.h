//
// Created by rodion on 8/25/20.
//

#ifndef TODOLIST_SRC_CLI_OPERATION_H_
#define TODOLIST_SRC_CLI_OPERATION_H_

#include <memory>
#include <States/StateInterface.h>
#include <States/AddTaskState.h>
#include <States/ExitState.h>
#include <States/GetTaskListState.h>
#include <States/GetTaskState.h>
#include <States/RemoveTaskState.h>
#include <States/StartState.h>
#include <States/ViewTaskState.h>
#include <States/ViewTaskListState.h>
#include <CommandParser.h>
#include <optional>

class Operation {
 public:
  Operation();

 public:
  static std::shared_ptr<Operation>   create(const Command&);

 public:
  Command                           getCommand() const;
  std::shared_ptr<StateInterface>   getNextState() const;

 private:
  Operation(std::shared_ptr<StateInterface> ptr,
            const Command& number, const unsigned int& argc);

 private:
  std::shared_ptr<StateInterface> pointer_;
  Command command_;
  unsigned int argc;
};

#endif //TODOLIST_SRC_CLI_OPERATION_H_
