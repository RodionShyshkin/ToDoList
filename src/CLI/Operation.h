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

//class StateInterface;

class Operation {
 public:
  Operation();

 public:
  static std::shared_ptr<Operation>   create(const std::string& command);

 public:
  std::string                       getCommand() const;
  std::shared_ptr<StateInterface>   getNextState() const;

 private:
  Operation(const std::string& command, std::unique_ptr<StateInterface> ptr,
            const Command& number, const unsigned int& argc);

 private:
  std::shared_ptr<StateInterface> pointer_;
  std::string command_;
  Command command_number_;
  unsigned int argc;
};

#endif //TODOLIST_SRC_CLI_OPERATION_H_
