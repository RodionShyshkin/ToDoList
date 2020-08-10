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

class DateTime {
 public:
  DateTime();
  DateTime(boost::gregorian::date due_date);
  DateTime(int year, int month, int day);

 public:
  static DateTime               get_current_date();

  boost::gregorian::date        get_date() const;

 public:
  bool operator< (DateTime date) const;

 private:
  tm                            time;
  boost::gregorian::date        due_date;
  boost::posix_time::ptime      due_time;
};

bool                            checkWeek(const DateTime &day);

#endif //TODOLIST__DUETIME_H_
