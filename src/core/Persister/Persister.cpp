//
// Created by rodion on 9/27/20.
//

#include "Persister.h"

Persister::Persister(const std::string &filepath, std::vector<ModelTaskDTO> &tasks) : filepath_(filepath), tasks_(tasks) { }

bool Persister::Save() {
  std::ofstream file(this->filepath_);
  if(!file.is_open()) return false;

  auto storage = StorageToProtoConverter::ConvertStorageToProto(this->tasks_);
  if(storage.SerializeToOstream(&file)) return false;

  file.close();
  return true;
}

bool Persister::Load() {
  StorageProto storage;
  std::ifstream file(this->filepath_);
  if(!file.is_open()) return false;

  if(!storage.ParseFromIstream(&file)) return false;
  file.close();

  this->tasks_ = ProtoToStorageConverter::Convert(storage);
  return true;
}