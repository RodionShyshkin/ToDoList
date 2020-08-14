//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_GENERATEID_H_
#define TODOLIST_SRC_GENERATEID_H_

#include "MemoryModel/Task/TaskID.h"

/*
 * Class which generates a counter of {TaskID} instances.
 *
 * @author Rodion Shyshkin
 */

class IDGenerator {
 public:
  IDGenerator();
  ~IDGenerator();

 public:
  /*
   * Generates task identifier {TaskID} and increases amount of IDs.
   *
   * @return TaskID generated ID
   */
  std::optional<TaskID>            GenerateID();

 private:
  unsigned int                     ids_amount_;
};

#endif //TODOLIST_SRC_GENERATEID_H_
