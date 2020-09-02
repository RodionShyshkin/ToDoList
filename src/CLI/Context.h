//
// Created by rodion on 8/26/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_H_
#define TODOLIST_SRC_CLI_CONTEXT_H_

#include <memory>
#include <API/TaskService.h>
#include <ContextInterface.h>
#include "ListModifier.h"

class Context : public ContextInterface {
 public:
  struct AddTask {
    std::string name_;
    std::string label_;
    Priority priority_;
    boost::gregorian::date date_;
    unsigned int parent_id_;
  };

  struct ShowList {
    ListModifier modifier_;
    bool is_sorted_;
  };

 public:
  AddTask add_task_struct_;
  ShowList show_list_struct_;

 public:
  std::unique_ptr<TaskService> service_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_H_
