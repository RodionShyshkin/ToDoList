//
// Created by rodion on 9/9/20.
//

#include <iostream>
#include "AddTaskBuffer.h"

AddTaskBuffer::AddTaskBuffer() {
  this->clearBuffer();
}

void AddTaskBuffer::clearBuffer() {
  this->name_ = "";
  this->label_ = "";
  this->priority_ = Priority::EMPTY;
  this->date_ = boost::gregorian::date{boost::gregorian::not_a_date_time};
  this->parent_id_ = 0;
  this->is_subtask_ = false;
}

bool AddTaskBuffer::checkBufferFullness() const {
  if(this->name_ == "") return false;
  if(this->is_subtask_ && this->parent_id_ == 0) return false;
  return true;
}

void AddTaskBuffer::setName(const std::string &name) { this->name_ = name; }

void AddTaskBuffer::setLabel(const std::string &label) { this->label_ = label; }

void AddTaskBuffer::setPriority(const Priority &priority) { this->priority_ = priority; }

void AddTaskBuffer::setDate(const boost::gregorian::date &date) { this->date_ = date; }

void AddTaskBuffer::setParent(const unsigned int &parent) {
  this->is_subtask_ = true;
  this->parent_id_ = parent;
}

std::string AddTaskBuffer::getName() const { return this->name_; }

std::string AddTaskBuffer::getLabel() const { return this->label_; }

Priority AddTaskBuffer::getPriority() const { return this->priority_; }

boost::gregorian::date AddTaskBuffer::getDate() const { return this->date_; }

unsigned int AddTaskBuffer::getParent() const {
  if(!this->is_subtask_) return 0;
  return this->parent_id_;
}