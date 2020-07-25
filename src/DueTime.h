//
// Created by rodion on 7/17/20.
//

#ifndef TODOLIST_SRC_DUETIME_H_
#define TODOLIST_SRC_DUETIME_H_

#include "DateTime.h"

class DueTime {
 public:
  DueTime();
  DueTime(const DateTime& time);
  ~DueTime();

 public:
  DateTime getTime() const;

 public:
//  DateTime addWeek(const DateTime &oldtime);

 public:
  friend std::ostream& operator<< (std::ostream &out, const DueTime &duetime);
  friend bool operator== (const DueTime &lhs, const DueTime &rhs);
  friend bool operator< (const DueTime &lhs, const DueTime &rhs);
  friend bool operator<= (const DueTime &lhs, const DueTime &rhs);
  friend bool operator> (const DueTime &lhs, const DueTime &rhs);

 private:
  DateTime time_;
};

DateTime getCurrentTime();
DateTime addWeek(const DateTime &oldtime);

#endif //TODOLIST_SRC_DUETIME_H_
