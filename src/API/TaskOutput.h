//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_TASKOUTPUT_H_
#define TODOLIST_SRC_TASKOUTPUT_H_

#include "FullTaskDTO.h"

std::string PriorityToString(Task::Priority priority);
std::string StatusToString(bool status);

class TaskOutput {
 public:
  /*static void printTask(const FullTaskDTO &task) {
    std::cout << "Task #" << task.getUserID() << ": " << task.getName() << " (" << task.getLabel() << "). Priority: "
              << PriorityToString(task.getPriority()) << ". Deadline: " << task.getDueTime() << ". Status: " << StatusToString(task.getStatus()) << std::endl;
  }*/
};

#endif //TODOLIST_SRC_TASKOUTPUT_H_
