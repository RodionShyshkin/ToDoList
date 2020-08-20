//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
//#include <StateInterface.h>
#include <API/TaskService.h>

class StateInterface;

class Context {
 public:
  Context();

 public:
  void changeState(std::shared_ptr<StateInterface>& newstate);

  void readState();
  void printState();

  void execute();


 private:
//  std::unique_ptr<TaskService> ts_;
  std::shared_ptr<StateInterface> state_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
