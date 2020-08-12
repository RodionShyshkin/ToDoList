//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_GENERATEID_H_
#define TODOLIST_SRC_GENERATEID_H_

#include <iostream>
#include "TaskID.h"

class IDGenerator {
 public:
  IDGenerator();
  ~IDGenerator();

 public:
  TaskID            GenerateID();

 private:
  unsigned int      ids_amount_;
};

#endif //TODOLIST_SRC_GENERATEID_H_
