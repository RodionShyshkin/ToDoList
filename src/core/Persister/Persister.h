//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_

#include <Persister/PersisterInterface.h>
#include <fstream>

class Persister : public PersisterInterface {
 public:
  Persister(const std::string& filepath, StorageProto& storage);

 public:
  bool Save() override;
  bool Load() override;

 private:
  std::string filepath_;
  StorageProto& storage_;
};

#endif //TODOLIST_SRC_CORE_PERSISTER_PERSISTER_H_
