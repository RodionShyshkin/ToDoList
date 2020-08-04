//
// Created by rodion on 7/21/20.
//

#ifndef TODOLIST_SRC_FULLTASKDTO_H_
#define TODOLIST_SRC_FULLTASKDTO_H_

#include "TaskEntity.h"

class TaskDTO {
 public:
  TaskDTO();
  TaskDTO(const TaskEntity& task);
  ~TaskDTO();

 public:
  TaskID getID() const;
  std::string getName() const;
  std::string getLabel() const;
  Task::Priority getPriority() const;
  DueTime getDueTime() const;
  bool getStatus() const;

 private:
  TaskEntity task;
};

#endif //TODOLIST_SRC_FULLTASKDTO_H_
