//
// Created by rodion on 7/16/20.
//

#include "Date.h"

bool Date::CheckWeek(const Date& date) {
  auto now = Date::GetCurrentDate();
  auto add_week = now.GetDate().day_number() + 7 - now.GetDate().day_of_week();

  if(date.GetDate().day_number() >= now.GetDate().day_number() &&
      date.GetDate().day_number() <= add_week) return true;
  else return false;
}

Date::Date() = default;

Date::Date(boost::gregorian::date due_date) {
  due_date_ = due_date;
}

Date::Date(std::string str) {
  due_date_ = boost::gregorian::from_string(str);
}

Date::Date(int year, int month, int day) {
  due_date_ = boost::gregorian::date(boost::gregorian::greg_year(year), boost::gregorian::greg_month(month),
                                           boost::gregorian::greg_day(day));
}

boost::gregorian::date Date::GetDate() const {
  return due_date_;
}

Date Date::GetCurrentDate()  {
  return Date(boost::gregorian::day_clock::local_day());
}

bool operator< (const Date& lhs, const Date& rhs) {
  return lhs.GetDate() < rhs.GetDate();
}
