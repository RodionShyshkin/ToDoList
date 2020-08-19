//
// Created by rodion on 8/18/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_IDGENERATORINTERFACE_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_IDGENERATORINTERFACE_H_

#include <MemoryModel/Task/TaskID.h>

class IDGeneratorInterface {
 public:
  virtual ~IDGeneratorInterface() = default;

 public:
  virtual std::optional<TaskID> GenerateID() = 0;
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_IDGENERATORINTERFACE_H_
