//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_

#include <Persister/PersisterInterface.h>
#include <Persister/Serialization/ProtoToStorageConverter.h>
#include <Persister/Serialization/StorageToProtoConverter.h>
#include <fstream>

class FilePersister : public PersisterInterface {
 public:
  FilePersister(std::fstream& file, TaskModelInterface& model);

 public:
  bool Save() override;
  bool Load() override;

 private:
  std::fstream file_;
  TaskModelInterface& model_;
};

#endif //TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_