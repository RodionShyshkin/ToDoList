//
// Created by rodion on 9/27/20.
//

#include "FilePersister.h"

FilePersister::FilePersister(const std::string &filepath, TaskModelInterface &model) : filepath_(filepath), model_(model) { }

bool FilePersister::Save() {
  std::ofstream file(this->filepath_);
  if(!file.is_open()) return false;

  auto storage = StorageToProtoConverter::ConvertStorageToProto(this->model_.getAllTasks());
  if(storage.SerializeToOstream(&file)) return false;

  file.close();
  return true;
}

bool FilePersister::Load() {
  StorageProto storage;
  std::ifstream file(this->filepath_);
  if(!file.is_open()) return false;

  if(!storage.ParseFromIstream(&file)) return false;
  file.close();

  this->model_ = ProtoToStorageConverter::Convert(storage);
  return true;
}