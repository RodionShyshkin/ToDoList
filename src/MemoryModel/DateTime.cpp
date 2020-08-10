//
// Created by rodion on 7/16/20.
//

#include "DateTime.h"

bool checkWeek(const DateTime& date) {
  auto now = DateTime::get_current_date();
  auto add_week = now.get_date().day_number() + 7 - now.get_date().day_of_week();

  if(date.get_date().day_number() >= now.get_date().day_number() &&
      date.get_date().day_number() <= add_week) return true;
  else return false;
}


DateTime::DateTime() = default;

DateTime::DateTime(boost::gregorian::date due_date) {
  this->due_date = due_date;
}

DateTime::DateTime(int year, int month, int day) {
  this->due_date = boost::gregorian::date(boost::gregorian::greg_year(year), boost::gregorian::greg_month(month),
                                            boost::gregorian::greg_day(day));
}

boost::gregorian::date DateTime::get_date() const {
  return this->due_date;
}

DateTime DateTime::get_current_date() {
  return DateTime(boost::gregorian::day_clock::local_day());
}

bool DateTime::operator< (DateTime date) const {
  return this->get_date() < date.get_date();
}
