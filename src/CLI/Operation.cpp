//
// Created by rodion on 8/25/20.
//

#include <States/PostponeTaskState.h>
#include <States/CompleteTaskState.h>
#include "Operation.h"

Operation::Operation() {
  this->argc = 0;
  this->pointer_ = std::make_unique<StartState>();
}

Operation::Operation(std::shared_ptr<StateInterface> ptr,
                     const Command& command,
                     const unsigned int &argc) {
  this->command_ = command;
  this->pointer_ = std::move(ptr);
  this->argc = argc;
}

std::shared_ptr<Operation> Operation::create(const Command& operation) {
  if(operation == Command::UNKNOWN) return nullptr;
  if(operation == Command::GETTASK) {
    return std::make_shared<Operation>(Operation{std::make_shared<GetTaskState>(), operation, 1});
  }
  if(operation == Command::ADDTASK) {
    return std::make_shared<Operation>(Operation{std::make_shared<AddTaskState>(), operation, 1});
  }
  if(operation == Command::EXIT) {
    return std::make_shared<Operation>(Operation{std::make_shared<ExitState>(), operation, 0});
  }
  if(operation == Command::REMOVETASK) {
    return std::make_shared<Operation>(Operation{std::make_shared<RemoveTaskState>(std::nullopt), operation, 1});
  }
  if(operation == Command::POSTPONETASK) {
    return std::make_shared<Operation>(Operation{std::make_shared<PostponeTaskState>(std::nullopt), operation, 2});
  }
  if(operation == Command::COMPLETETASK) {
    return std::make_shared<Operation>(Operation{std::make_shared<CompleteTaskState>(std::nullopt), operation, 0});
  }
  if(operation == Command::GETTASKLIST) {
    return std::make_shared<Operation>(Operation{std::make_shared<GetTaskListState>(), operation, 0});
  }
  if(operation == Command::MAINMENU) {
    return std::make_shared<Operation>(Operation{std::make_shared<StartState>(), operation, 0});
  }
  return nullptr;
}

Command Operation::getCommand() const {
  return command_;
}

std::shared_ptr<StateInterface> Operation::getNextState() const {
  return pointer_;
}