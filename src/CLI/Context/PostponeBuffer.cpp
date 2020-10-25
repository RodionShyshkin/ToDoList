//
// Created by rodion on 9/9/20.
//

#include "PostponeBuffer.h"

PostponeBuffer::PostponeBuffer() {
  clearBuffer();
}

void PostponeBuffer::clearBuffer() {
  new_date_ = boost::gregorian::date{boost::gregorian::not_a_date_time};
}

bool PostponeBuffer::checkBufferFullness() const {
  return (!new_date_.is_not_a_date());
}

void PostponeBuffer::setNewDate(const boost::gregorian::date &date) {
  new_date_ = date;
}

boost::gregorian::date PostponeBuffer::getNewDate() const {
  return new_date_;
}