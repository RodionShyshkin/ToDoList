//
// Created by rodion on 7/17/20.
//

#include <memory>
#include "DueTime.h"

DueTime::DueTime() = default;
DueTime::DueTime(const DateTime& time) : time_(time) {}
DueTime::~DueTime() = default;


DateTime DueTime::getTime() const { return time_; }

std::ostream& operator<< (std::ostream &out, const DueTime &duetime) {
  out << duetime.time_;
  return out;
}
bool operator== (const DueTime &lhs, const DueTime &rhs) { return (lhs.time_ == rhs.time_); }
bool operator< (const DueTime &lhs, const DueTime &rhs) { return lhs.time_ < rhs.time_; }
bool operator<= (const DueTime &lhs, const DueTime &rhs) { return (lhs == rhs && lhs < rhs); }
bool operator> (const DueTime &lhs, const DueTime &rhs) { return (lhs.time_ > rhs.time_); }

