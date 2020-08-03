//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DUETIME_H_
#define TODOLIST__DUETIME_H_

#include <ctime>
#include <iostream>

class DateTime {
 public:
  DateTime();
  DateTime(int year, int month, int day, int hours, int minutes);
  DateTime(tm tmtime);
  ~DateTime();

 public:
  [[nodiscard]] unsigned int    getYear() const;
  [[nodiscard]] unsigned int    getMonth() const;
  [[nodiscard]] unsigned int    getDay() const;
  [[nodiscard]] unsigned int    getHours() const;
  [[nodiscard]] unsigned int    getMinutes() const;

 public:
  void                          setYear(unsigned int value);
  void                          setMonth(unsigned int value);
  void                          setDay(unsigned int value);

 public:
  friend bool                   operator== (const DateTime &lhs, const DateTime &rhs);
  friend bool                   operator< (const DateTime &lhs, const DateTime &rhs);
  friend bool                   operator> (const DateTime& lhs, const DateTime& rhs);

 private:
  tm                            time;
};

unsigned int                    getDaysCount(unsigned int month, unsigned int year);
DateTime                        getCurrentTime();
DateTime                        addWeek(const DateTime &oldtime);

#endif //TODOLIST__DUETIME_H_
