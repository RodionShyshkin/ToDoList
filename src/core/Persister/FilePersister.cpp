//
// Created by rodion on 9/27/20.
//

#include "FilePersister.h"

FilePersister::FilePersister(std::fstream &&file, TaskModelInterface &model) : file_(std::move(file)), model_(model) { }

bool FilePersister::Save() {
  if(!file_.is_open()) return false;

  proto::StorageProto storage;
  proto_converter::StorageToProto(model_.GetAllTasks(), storage);
  if(!storage.SerializeToOstream(&file_)) return false;

  file_.close();
  return true;
}

bool FilePersister::Load() {
  if(!file_.is_open()) return false;
  proto::StorageProto storage;

  if(!storage.ParseFromIstream(&file_)) return false;
  file_.close();

  if(!proto_converter::ProtoToModel(storage, model_)) return false;
  return true;
}