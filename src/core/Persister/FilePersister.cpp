//
// Created by rodion on 9/27/20.
//

#include "FilePersister.h"

FilePersister::FilePersister(std::fstream &file, TaskModelInterface &model) : file_(std::move(file)), model_(model) { }

bool FilePersister::Save() {
  if(!file_.is_open()) return false;

  auto storage = StorageToProtoConverter::ConvertStorageToProto(model_.getAllTasks());
  if(!storage.SerializeToOstream(&file_)) return false;

  file_.close();
  return true;
}

bool FilePersister::Load() {
  if(!file_.is_open()) return false;
  StorageProto storage;

  if(!storage.ParseFromIstream(&file_)) return false;
  file_.close();

  ProtoToStorageConverter::ConvertProtoToStorage(storage, model_);
  return true;
}