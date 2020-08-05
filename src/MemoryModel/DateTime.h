//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DUETIME_H_
#define TODOLIST__DUETIME_H_

#include <ctime>
#include <iostream>
#include <memory>
//#include <boost/chrono.hpp>
//#include <boost/chrono/chrono_io.hpp>
//#include <boost/chrono/duration.hpp>

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
  void                          setYear(const unsigned int& value);
  void                          setMonth(const unsigned int& value);
  void                          setDay(const unsigned int& value);
  void                          setHours(const unsigned int& value);
  void                          setMinutes(const unsigned int& value);

  DateTime                      validateTime();

 public:
  bool                          operator==(DateTime time) const;
  bool                          operator< (DateTime time) const;
  bool                          operator> (DateTime time) const;
  bool                          operator<= (DateTime time) const;
  bool                          operator>= (DateTime time) const;

 private:
  tm                            time;
};

unsigned int                    getDaysCount(unsigned int month, unsigned int year);
DateTime                        getCurrentTime();
DateTime                        addWeek(const DateTime &oldtime);
DateTime                        updateTime(std::shared_ptr<DateTime> time);

#endif //TODOLIST__DUETIME_H_
