//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_
#define TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_

#include <string>
#include <task.pb.h>
#include <src/core/MemoryModel/Storage/FullStorage.h>

class PersisterInterface {
 public:
  virtual ~PersisterInterface() = default;

 public:
  virtual bool      Save(const std::string& filepath, const StorageProto&);
  virtual bool      Load(const std::string& filepath, std::unique_ptr<FullStorage>& storage);
};

#endif //TODOLIST_SRC_CORE_PERSISTER_PERSISTERINTERFACE_H_
