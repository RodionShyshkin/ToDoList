//
// Created by rodion on 7/16/20.
//

#include "DueTime.h"

DueTime::DueTime() = default;

DueTime::DueTime(int year, int month, int day, int hours, int minutes, int seconds) {
  tm temp = {seconds, minutes, hours, day, month, year};
  this->time = temp;
}

DueTime::~DueTime() = default;

int DueTime::getYear() const { return time.tm_year; }
int DueTime::getMonth() const { return time.tm_mon; }
int DueTime::getDay() const { return time.tm_mday; }
int DueTime::getHours() const { return time.tm_hour; }
int DueTime::getMinutes() const { return time.tm_min; }
int DueTime::getSeconds() const { return time.tm_sec; }

std::ostream& operator<< (std::ostream &out, const DueTime &duetime) {
  out << duetime.getYear() << "-" << duetime.getMonth() << "-" << duetime.getDay() << " " << duetime.getHours() << ":" << duetime.getMinutes() <<
  ":" << duetime.getSeconds();
  return out;
}

std::istream& operator>> (std::istream &in, DueTime &duetime) {
  in >> duetime.time.tm_year >> duetime.time.tm_mon >> duetime.time.tm_mday >> duetime.time.tm_hour >> duetime.time.tm_min >> duetime.time.tm_sec;
  return in;
}

