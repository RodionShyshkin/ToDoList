//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DUETIME_H_
#define TODOLIST__DUETIME_H_

#include <ctime>
#include <iostream>

class DueTime {
 public:
  DueTime();
  DueTime(int year, int month, int day, int hours, int minutes, int seconds);

 public:
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  int getHours() const;
  int getMinutes() const;
  int getSeconds() const;

 public:
  friend std::ostream& operator<< (std::ostream &out, const DueTime &duetime);
  friend std::istream& operator>> (std::istream &in, DueTime &duetime);

 private:
  tm time;
};

#endif //TODOLIST__DUETIME_H_
