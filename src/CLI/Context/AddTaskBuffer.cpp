//
// Created by rodion on 9/9/20.
//

#include "AddTaskBuffer.h"

AddTaskBuffer::AddTaskBuffer() {
  this->clearBuffer();
}

void AddTaskBuffer::clearBuffer() {
  name_ = "";
  label_ = "";
  priority_ = Priority::EMPTY;
  date_ = boost::gregorian::date{boost::gregorian::not_a_date_time};
  is_subtask_ = false;
}

bool AddTaskBuffer::checkBufferFullness() const {
  if(name_ == "") return false;
  return true;
}

void AddTaskBuffer::setName(const std::string &name) { name_ = name; }

void AddTaskBuffer::setLabel(const std::string &label) { label_ = label; }

void AddTaskBuffer::setPriority(const Priority &priority) { priority_ = priority; }

void AddTaskBuffer::setDate(const boost::gregorian::date &date) { date_ = date; }

std::string AddTaskBuffer::getName() const { return name_; }

std::string AddTaskBuffer::getLabel() const { return label_; }

Priority AddTaskBuffer::getPriority() const { return priority_; }

boost::gregorian::date AddTaskBuffer::getDate() const { return date_; }