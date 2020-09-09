//
// Created by rodion on 9/9/20.
//

#include "ShowListBuffer.h"

ShowListBuffer::ShowListBuffer() {
  this->clearBuffer();
}

void ShowListBuffer::clearBuffer() {
  this->modifier_ = ListModifier::UNKNOWN;
  this->is_sorted_ = false;
}

bool ShowListBuffer::checkBufferFullness() const {
  return (this->modifier_ != ListModifier::UNKNOWN && !this->is_sorted_);
}

void ShowListBuffer::setModifier(const ListModifier &modifier) { this->modifier_ = modifier; }

void ShowListBuffer::setSortedFlag(const bool &flag) { this->is_sorted_ = flag; }

ListModifier ShowListBuffer::getModifier() const { return this->modifier_; }

bool ShowListBuffer::getSortedFlag() const { return this->is_sorted_; }