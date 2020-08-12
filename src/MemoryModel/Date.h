//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DATETIME_H_
#define TODOLIST__DATETIME_H_

#include <ctime>
#include <iostream>
#include <memory>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

class Date {
 public:
  Date();
  Date(boost::gregorian::date due_date);
  Date(int year, int month, int day);

 public:
  static Date                   GetCurrentDate();
  static bool                   CheckWeek(const Date& day);
  boost::gregorian::date        GetDate() const;

 private:
  boost::gregorian::date        due_date_;
};

bool operator< (const Date& lhs, const Date& rhs);

#endif //TODOLIST__DUETIME_H_
