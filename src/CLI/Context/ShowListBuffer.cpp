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
  this->label_ = "";
  this->list_.clear();
  this->is_by_label_ = false;
}

bool ShowListBuffer::checkBufferFullness() const {
  if(!this->is_by_label_ && !this->label_.empty()) return false;
  return (this->modifier_ != ListModifier::UNKNOWN);
}

void ShowListBuffer::setModifier(const ListModifier &modifier) {
  this->modifier_ = modifier;
  if(this->modifier_ == ListModifier::BY_LABEL) this->is_by_label_ = true;
}

void ShowListBuffer::setSortedFlag(const bool &flag) { this->is_sorted_ = flag; }

void ShowListBuffer::setLabel(const std::string& label) { this->label_ = label; }

void ShowListBuffer::setList(const std::vector<TaskDTO>& list) { this->list_ = list; }

ListModifier ShowListBuffer::getModifier() const { return this->modifier_; }

bool ShowListBuffer::getSortedFlag() const { return this->is_sorted_; }

std::string ShowListBuffer::getLabel() const { return this->label_; }

std::vector<TaskDTO> ShowListBuffer::getList() const { return this->list_; }

bool ShowListBuffer::getByLabelFlag() const { return this->is_by_label_; }