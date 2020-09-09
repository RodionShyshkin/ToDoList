//
// Created by rodion on 9/9/20.
//

#include "PostponeBuffer.h"

PostponeBuffer::PostponeBuffer() {
  this->clearBuffer();
}

void PostponeBuffer::clearBuffer() {
  this->is_single_task_ = false;
  this->new_date_ = boost::gregorian::date{boost::gregorian::not_a_date_time};
}

bool PostponeBuffer::checkBufferFullness() const {
  return (!this->is_single_task_ && !this->new_date_.is_not_a_date());
}

void PostponeBuffer::setSingleTaskFlag(const bool &flag) {
  this->is_single_task_ = flag;
}

void PostponeBuffer::setNewDate(const boost::gregorian::date &date) {
  this->new_date_ = date;
}

bool PostponeBuffer::getSingleTaskFlag() const {
  return this->is_single_task_;
}

boost::gregorian::date PostponeBuffer::getNewDate() const {
  return this->new_date_;
}