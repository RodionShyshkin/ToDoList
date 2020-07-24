//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DUETIME_H_
#define TODOLIST__DUETIME_H_

#include "time.h"
#include <iostream>

class DateTime {
 public:
  DateTime();
  DateTime(int year, int month, int day, int hours, int minutes);
  DateTime(tm tmtime);
  ~DateTime();

 public:
  unsigned int getYear() const;
  unsigned int getMonth() const;
  unsigned int getDay() const;
  unsigned int getHours() const;
  unsigned int getMinutes() const;

 public:
  void setYear(unsigned int value);
  void setMonth(unsigned int value);
  void setDay(unsigned int value);
  void setHours(unsigned int value);
  void setMinutes(unsigned int value);

 public:
  friend std::ostream& operator<< (std::ostream &out, const DateTime &time);
  friend std::istream& operator>> (std::istream &in, DateTime &time);
  friend bool operator== (const DateTime &lhs, const DateTime &rhs);
  friend bool operator!= (const DateTime &lhs, const DateTime &rhs);
  friend bool operator< (const DateTime &lhs, const DateTime &rhs);
  friend DateTime& operator+ (const DateTime &lhs, const DateTime &rhs);

 private:
  tm time;
};

unsigned int getDaysCount(unsigned int month);

#endif //TODOLIST__DUETIME_H_
