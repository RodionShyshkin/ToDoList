//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
#include <API/TaskService.h>
#include <ContextInterface.h>
#include <Context/IDBuffer.h>
#include <Context/AddTaskBuffer.h>
#include "ListModifier.h"

class Context : public ContextInterface {
 public:
  struct ShowList {
    ListModifier modifier_;
    bool is_sorted_;
  };

  struct PostponeDate {
    boost::gregorian::date new_date_;
    unsigned int id_;
    bool is_single_task_;
  };

 public:
  void clearAddTaskBuffer();
  void clearShowListBuffer();
  void clearPostponeBuffer();
  void resetContext();

 public:
  AddTaskBuffer add_task_buffer_;
  ShowList show_list_struct_;
  IDBuffer id_buffer_;
  PostponeDate postpone_date_;

 public:
  std::unique_ptr<TaskService> service_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
