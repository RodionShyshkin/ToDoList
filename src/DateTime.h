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
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  int getHours() const;
  int getMinutes() const;

 public:
  friend std::ostream& operator<< (std::ostream &out, const DateTime &time);
  friend std::istream& operator>> (std::istream &in, DateTime &time);
  friend bool operator== (const DateTime &lhs, const DateTime &rhs);
  friend bool operator!= (const DateTime &lhs, const DateTime &rhs);
  friend bool operator< (const DateTime &lhs, const DateTime &rhs);
  friend bool operator> (const DateTime& lhs, const DateTime &rhs);

 private:
  tm time;
};

#endif //TODOLIST__DUETIME_H_
