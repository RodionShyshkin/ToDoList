//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_GENERATEID_H_
#define TODOLIST_SRC_GENERATEID_H_

#include <iostream>
#include "TaskID.h"

class GenerateID {
 public:
  GenerateID();
  ~GenerateID();

 public:
  TaskID            generateID();

 private:
  unsigned int      ids;
};

#endif //TODOLIST_SRC_GENERATEID_H_
