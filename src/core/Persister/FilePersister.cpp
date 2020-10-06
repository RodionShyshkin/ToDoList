//
// Created by rodion on 9/27/20.
//

#include "FilePersister.h"

FilePersister::FilePersister(std::fstream &file, TaskModelInterface &model) : file_(std::move(file)), model_(model) { }

bool FilePersister::Save() {
  if(!this->file_.is_open()) return false;

  auto storage = StorageToProtoConverter::ConvertStorageToProto(this->model_.getAllTasks());
  if(storage.SerializeToOstream(&this->file_)) return false;

  this->file_.close();
  return true;
}

bool FilePersister::Load() {
  if(!this->file_.is_open()) return false;
  StorageProto storage;

  if(!storage.ParseFromIstream(&this->file_)) return false;
  this->file_.close();

  this->model_ = ProtoToStorageConverter::ConvertProtoToStorage(storage);
  return true;
}