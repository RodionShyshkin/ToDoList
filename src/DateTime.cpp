//
// Created by rodion on 7/16/20.
//

#include "DateTime.h"
#include <exception>

DateTime::DateTime() = default;

DateTime::DateTime(int year, int month, int day, int hours, int minutes) {
  if(year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1) throw std::invalid_argument("Invalid date.");
  if((month == 2 || year % 4 == 0) && day > 29) throw std::invalid_argument("Invalid date.");
  if((month == 2 || year % 4 != 0) && day > 28) throw std::invalid_argument("Invalid date.");
  if((month == 1 || month == 4 || month == 6 || month == 9 || month == 1) && day > 30) throw std::invalid_argument("Invalid date.");
  if((month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) & day > 31) throw std::invalid_argument("Invalid date.");
  if(hours < 0 || hours > 24 || minutes < 0 || minutes > 59) throw std::invalid_argument("Invalid time.");

  this->time = {0, minutes, hours, day, month, year};
}

DateTime::DateTime(tm tmtime) : DateTime(tmtime.tm_year, tmtime.tm_mon, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min) { }
DateTime::~DateTime() = default;


int DateTime::getYear() const { return time.tm_year; }
int DateTime::getMonth() const { return time.tm_mon; }
int DateTime::getDay() const { return time.tm_mday; }
int DateTime::getHours() const { return time.tm_hour; }
int DateTime::getMinutes() const { return time.tm_min; }


std::ostream& operator<< (std::ostream &out, const DateTime &time) {
  out << time.time.tm_year << "-" << time.time.tm_mon << "-" << time.time.tm_mday << " " << time.time.tm_hour << ":" << time.time.tm_min;
  return out;
}
std::istream& operator>> (std::istream &in, DateTime &time) {
  in >> time.time.tm_year >> time.time.tm_mon >> time.time.tm_mday >> time.time.tm_hour >> time.time.tm_min;
  return in;
}
bool operator== (const DateTime &lhs, const DateTime &rhs) {
  if(lhs.getMinutes() != rhs.getMinutes()) return false;
  if(lhs.getHours() != rhs.getHours()) return false;
  if(lhs.getDay() != rhs.getDay()) return false;
  if(lhs.getMonth() != rhs.getMonth()) return false;
  if(lhs.getYear() != rhs.getYear()) return false;
  return true;
}
bool operator!= (const DateTime &lhs, const DateTime &rhs) { return !(lhs == rhs); }
bool operator< (const DateTime &lhs, const DateTime &rhs) {
  if(lhs.getMinutes() != rhs.getMinutes()) return false;
  if(lhs.getHours() != rhs.getHours()) return false;
  if(lhs.getDay() != rhs.getDay()) return false;
  if(lhs.getMonth() != rhs.getMonth()) return false;
  if(lhs.getYear() != rhs.getYear()) return false;
  return true;
}
