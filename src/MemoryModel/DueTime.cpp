//
// Created by rodion on 7/17/20.
//

#include "DueTime.h"

DueTime::DueTime() = default;
DueTime::DueTime(const DateTime& time) : time_(time) {}
DueTime::~DueTime() = default;


DateTime DueTime::getTime() const { return time_; }

bool DueTime::operator==(DueTime time) const {
  return (this->getTime() == time.getTime());
}
bool DueTime::operator<(DueTime time) const {
  return (this->getTime() < time.getTime());
}
bool DueTime::operator>(DueTime time) const {
  return (this->getTime() > time.getTime());
}
bool DueTime::operator<=(DueTime time) const {
  return (this->getTime() <= time.getTime());
}
bool DueTime::operator>=(DueTime time) const {
  return (this->getTime() >= time.getTime());
}
