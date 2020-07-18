//
// Created by rodion on 7/17/20.
//

#include <memory>
#include "DueTime.h"

DueTime::DueTime() = default;

DueTime::DueTime(const DateTime& time) : time_(time) {
  //... timer ...
}

DueTime::~DueTime() = default;

DateTime getCurrentTime() {
  time_t t = time(0);
  std::unique_ptr<struct tm> now(localtime(&t));
  return DateTime(now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min);
}

void DueTime::changeDueTime(const DateTime &newDueTime) {
  DueTime current = getCurrentTime();
  if(newDueTime <= current) throw std::invalid_argument("You can plan to do task in the past or just now.");
  this->time_ = newDueTime;
}

std::ostream& operator<< (std::ostream &out, const DueTime &duetime) {
  out << duetime.time_;
  return out;
}

bool operator== (const DueTime &lhs, const DueTime &rhs) {
  return (lhs.time_ == rhs.time_);
}

bool operator< (const DueTime &lhs, const DueTime &rhs) {
  return lhs.time_ < rhs.time_;
}

bool operator> (const DueTime &lhs, const DueTime &rhs) {
  return (lhs.time_ > rhs.time_);
}

bool operator<= (const DueTime &lhs, const DueTime &rhs) {
  return (lhs == rhs && lhs < rhs);
}