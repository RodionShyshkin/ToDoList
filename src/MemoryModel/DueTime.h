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
  bool operator== (DueTime time) const;
  bool operator< (DueTime time) const;
  bool operator> (DueTime time) const;
  bool operator<= (DueTime time) const;
  bool operator>= (DueTime time) const;

 private:
  DateTime                    time_;
};

#endif //TODOLIST_SRC_DUETIME_H_
