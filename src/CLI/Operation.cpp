//
// Created by rodion on 8/25/20.
//

#include "Operation.h"

Operation::Operation() {
  this->argc = 0;
  this->pointer_ = std::make_unique<StartState>();
  this->command_ = "";
}

Operation::Operation(const std::string &command,
                     std::unique_ptr<StateInterface> ptr,
                     const Command& com,
                     const unsigned int &argc) {
  this->command_ = command;
  this->pointer_ = std::move(ptr);
  this->argc = argc;
  this->command_number_ = com;
}

std::shared_ptr<Operation> Operation::create(const std::string &command) {
  auto operation = parseCommand(command);
  if(operation == Command::UNKNOWN) return nullptr;
  if(operation == Command::GETTASK) {
    return std::make_unique<Operation>(Operation{command, std::make_unique<GetTaskState>(), operation, 1});
  }
  if(operation == Command::ADDTASK) {
    return std::make_unique<Operation>(Operation{command, std::make_unique<AddTaskState>(), operation, 1});
  }
  if(operation == Command::EXIT) {
    return std::make_unique<Operation>(Operation{command, std::make_unique<ExitState>(), operation, 0});
  }
  return nullptr;
//  else if()
}

std::string Operation::getCommand() const {
  return command_;
}

std::shared_ptr<StateInterface> Operation::getNextState() const {
  return pointer_;
}