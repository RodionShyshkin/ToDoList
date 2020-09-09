//
// Created by rodion on 9/9/20.
//

#include "IDBuffer.h"

IDBuffer::IDBuffer() {
  this->clearBuffer();
}

void IDBuffer::clearBuffer() {
  this->has_id_ = false;
  this->id_ = 0;
}

bool IDBuffer::checkBufferFullness() const {
  return (this->has_id_ && this->id_ != 0);
}

void IDBuffer::setID(const unsigned int &newid) {
  this->id_ = newid;
  this->has_id_ = true;
}

std::optional<unsigned int> IDBuffer::getID() const {
  if(!this->has_id_) return std::nullopt;
  if(this->id_ == 0) return std::nullopt;
  return this->id_;
}