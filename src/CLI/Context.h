//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
#include <API/TaskService.h>
#include <StateStorage.h>

class StateInterface;

class Context {
 public:
  Context();

 private:
  std::unique_ptr<StateStorage> storage_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
