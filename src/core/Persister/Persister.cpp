//
// Created by rodion on 9/27/20.
//

#include "Persister.h"

bool Persister::SaveToDisk(const std::string &filepath, const StorageProto &storage) {
  std::ofstream file(filepath);
  if(!file.is_open()) return false;

  if(!storage.SerializeToOstream(&file)) return false;

  return true;
}

bool Persister::LoadFromDisk(const std::string &filepath, StorageProto& storage) {
  std::ifstream file(filepath);
  if(!file.is_open()) return false;

  if(!storage.ParseFromIstream(&file)) return false;

  file.close();
  return true;
}