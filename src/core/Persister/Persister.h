//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_

#include <Persister/PersisterInterface.h>
#include <fstream>

class Persister : public PersisterInterface {
 public:
  bool SaveToDisk(const std::string &filepath, const StorageProto &) override;
  bool LoadFromDisk(const std::string &filepath, StorageProto& storage) override;
};

#endif //TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_
