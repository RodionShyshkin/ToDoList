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
  [[nodiscard]] DateTime      getTime() const;

 public:
  friend bool                 operator== (const DueTime &lhs, const DueTime &rhs);
  friend bool                 operator< (const DueTime &lhs, const DueTime &rhs);
  friend bool                 operator> (const DueTime &lhs, const DueTime &rhs);
  friend bool                 operator<= (const DueTime& lhs, const DueTime& rhs);
  friend bool                 operator>= (const DueTime& lhs, const DueTime& rhs);

 private:
  DateTime                    time_;
};

#endif //TODOLIST_SRC_DUETIME_H_
