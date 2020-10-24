//
// Created by rodion on 9/9/20.
//

#include "IDBuffer.h"

IDBuffer::IDBuffer() {
  clearBuffer();
}

void IDBuffer::clearBuffer() {
  has_id_ = false;
}

bool IDBuffer::checkBufferFullness() const {
  return has_id_;
}

void IDBuffer::setID(const unsigned int &newid) {
  id_ = newid;
  has_id_ = true;
}

std::optional<unsigned int> IDBuffer::getID() const {
  if(!has_id_) return std::nullopt;
  return std::make_optional<unsigned int>(id_);
}