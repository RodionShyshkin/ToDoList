//
// Created by rodion on 9/27/20.
//

#include "Persister.h"

Persister::Persister(const std::string &filepath, StorageProto &storage) : filepath_(filepath), storage_(storage) { }

bool Persister::Save() {
  std::ofstream file(this->filepath_);
  if(!file.is_open()) return false;

  if(!this->storage_.SerializeToOstream(&file)) return false;

  return true;
}

bool Persister::Load() {
  std::ifstream file(this->filepath_);
  if(!file.is_open()) return false;

  if(!this->storage_.ParseFromIstream(&file)) return false;

  file.close();
  return true;
}