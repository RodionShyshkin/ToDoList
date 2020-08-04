//
// Created by rodion on 7/16/20.
//

#include "DateTime.h"

DateTime addWeek(const DateTime &oldtime) {
//  std::chrono::system_clock::time_point newerr = std::chrono::system_clock::now() + std::chrono::hours(24);
 //std::cout << newerr << std::endl;

  DateTime newtime = oldtime;
  newtime.setDay(newtime.getDay() + 7);
  if(newtime.getDay() > getDaysCount(newtime.getMonth(), newtime.getYear())) {
    newtime.setDay(newtime.getDay() % getDaysCount(newtime.getMonth(), newtime.getYear()));
    newtime.setMonth(newtime.getMonth() + 1);
    if(newtime.getMonth() > 12) {
      newtime.setMonth(1);
      newtime.setYear(newtime.getYear() + 1);
    }
  }
  return newtime;
}

DateTime getCurrentTime() {
 // auto local_time = boost::chrono::system_clock::now();

  time_t t = time(0);
  struct tm * now = localtime(&t);
  return DateTime(now->tm_year+1900, now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min);
}

unsigned int getDaysCount(unsigned int month, unsigned int year) {
  if(month == 4 || month == 6 || month == 9 || month == 11) return 30;
  if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
  if(month == 2 && year % 4 != 0) return 28;
  if(month == 2 && year % 4 == 0) return 29;
}



DateTime::DateTime() = default;

DateTime::DateTime(int year, int month, int day, int hours, int minutes) {
  if(year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1) throw std::invalid_argument("Invalid date.");
  if(day > getDaysCount(month, year)) throw std::invalid_argument("Invalid date.");
  if(hours < 0 || hours > 24 || minutes < 0 || minutes > 59) throw std::invalid_argument("Invalid time.");

  this->time = {0, minutes, hours, day, month, year};
}

DateTime::DateTime(tm tmtime) : DateTime(tmtime.tm_year+1900, tmtime.tm_mon+1, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min) { }
DateTime::~DateTime() = default;



unsigned int DateTime::getYear() const { return time.tm_year; }
unsigned int DateTime::getMonth() const { return time.tm_mon; }
unsigned int DateTime::getDay() const { return time.tm_mday; }
unsigned int DateTime::getHours() const { return time.tm_hour; }
unsigned int DateTime::getMinutes() const { return time.tm_min; }

void DateTime::setYear(unsigned int value) { this->time.tm_year = value; }
void DateTime::setMonth(unsigned int value) { this->time.tm_mon = value; }
void DateTime::setDay(unsigned int value) { this->time.tm_mday = value; }


bool operator== (const DateTime &lhs, const DateTime &rhs) {
  if(lhs.getMinutes() != rhs.getMinutes()) return false;
  if(lhs.getHours() != rhs.getHours()) return false;
  if(lhs.getDay() != rhs.getDay()) return false;
  if(lhs.getMonth() != rhs.getMonth()) return false;
  return lhs.getYear() == rhs.getYear();
}
bool operator< (const DateTime &lhs, const DateTime &rhs) {
  if(lhs.getYear() < rhs.getYear()) return true;
  else if(lhs.getYear() == rhs.getYear()) {
    if(lhs.getMonth() < rhs.getMonth()) return true;
    else if(lhs.getMonth() == rhs.getMonth()) {
      if(lhs.getDay() < rhs.getDay()) return true;
      else if(lhs.getDay() == rhs.getDay()) {
        if(lhs.getHours() < rhs.getHours()) return true;
        else if(lhs.getHours() == rhs.getHours()) {
          if(lhs.getMinutes() < rhs.getMinutes()) return true;
        }
      }
    }
  }
  return false;
}
bool operator> (const DateTime &lhs, const DateTime &rhs) {
  return !(lhs < rhs || lhs == rhs);
}
bool operator<= (const DateTime& lhs, const DateTime& rhs) {
  return (lhs < rhs || lhs == rhs);
}
bool operator>= (const DateTime& lhs, const DateTime& rhs) {
  return (lhs > rhs || lhs == rhs);
}

