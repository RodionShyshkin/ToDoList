//
// Created by rodion on 9/9/20.
//

#include "ShowListBuffer.h"

ShowListBuffer::ShowListBuffer() {
  clearBuffer();
}

void ShowListBuffer::clearBuffer() {
  modifier_ = ListModifier::UNKNOWN;
  is_sorted_ = false;
  label_ = "";
  list_.clear();
  is_by_label_ = false;
}

bool ShowListBuffer::checkBufferFullness() const {
  if(!is_by_label_ && !label_.empty()) return false;
  if(is_by_label_ && label_.empty()) return false;
  return (modifier_ != ListModifier::UNKNOWN);
}

void ShowListBuffer::setModifier(const ListModifier &modifier) {
  modifier_ = modifier;
  if(modifier_ == ListModifier::BY_LABEL) is_by_label_ = true;
}

void ShowListBuffer::setSortedFlag(const bool &flag) { is_sorted_ = flag; }

void ShowListBuffer::setLabel(const std::string& label) { label_ = label; }

void ShowListBuffer::setList(const std::vector<TaskDTO>& list) { list_ = list; }

ListModifier ShowListBuffer::getModifier() const { return modifier_; }

bool ShowListBuffer::getSortedFlag() const { return is_sorted_; }

std::string ShowListBuffer::getLabel() const { return label_; }

std::vector<TaskDTO> ShowListBuffer::getList() const { return list_; }

bool ShowListBuffer::getByLabelFlag() const { return is_by_label_; }