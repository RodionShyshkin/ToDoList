//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
#include <API/TaskService.h>
#include <Context/IDBuffer.h>
#include <Context/AddTaskBuffer.h>
#include <Context/ShowListBuffer.h>
#include <Context/PostponeBuffer.h>
#include <API/TaskServiceInterface.h>
#include <IO/IOInterface.h>

class Context {
 public:
  Context(const std::shared_ptr<TaskServiceInterface>&,
      const std::shared_ptr<IOInterface>&);

 public:
  void clearAllBuffers();

 public:
  AddTaskBuffer add_task_buffer_;
  ShowListBuffer show_list_buffer_;
  IDBuffer id_buffer_;
  PostponeBuffer postpone_buffer_;

 public:
  std::shared_ptr<TaskServiceInterface> service_;
  std::shared_ptr<IOInterface> io_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
