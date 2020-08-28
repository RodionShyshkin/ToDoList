//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
#include <API/TaskService.h>
#include <ContextInterface.h>

class Context : public ContextInterface {
 public:

 private:
  std::unique_ptr<TaskService> service_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
