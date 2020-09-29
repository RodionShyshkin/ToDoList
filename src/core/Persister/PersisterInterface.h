//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_
#define TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_

#include <string>
#include <task.pb.h>
#include <src/core/MemoryModel/Storage/TaskModel.h>

class PersisterInterface {
 public:
  virtual ~PersisterInterface() = default;

 public:
  virtual bool      Save() = 0;
  virtual bool      Load() = 0;
};

#endif //TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_