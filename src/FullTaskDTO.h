//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_FULLTASKDTO_H_
#define TODOLIST_SRC_FULLTASKDTO_H_

#include "FullTask.h"

class FullTaskDTO {
 public:
  FullTaskDTO(std::shared_ptr<FullTask> task);
  ~FullTaskDTO();

 public:
  TaskID getID() const;
  std::string getName() const;
  std::string getLabel() const;
  Task::Priority getPriority() const;
  DueTime getDueTime() const;
  bool getStatus() const;

 private:
  std::shared_ptr<FullTask> task;
};

#endif //TODOLIST_SRC_FULLTASKDTO_H_
