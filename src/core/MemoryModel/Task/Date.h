//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__DATETIME_H_
#define TODOLIST__DATETIME_H_

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

/*
 * \brief Date wrapper.
 *
 * This class wraps boost date and implements functions we need to use when we manage our tasks.
 *
 * @author Rodion Shyshkin
 */

class Date {
 public:
  Date();
  Date(boost::gregorian::date due_date);
  Date(std::string str);
  Date(int year, int month, int day);


 public:

  /*
   * Gives a current local time.
   *
   * @return Date current local time
   */
  static Date                   GetCurrentDate();

  /*
   * Check if the date belong to this week.
   *
   * @param Date the date which we need to check.
   *
   * @return bool True if this week, False in another case.
   */
  static bool                   CheckWeek(const Date& day);

  boost::gregorian::date        GetDate() const;

 private:
  boost::gregorian::date        due_date_;
};

bool operator< (const Date& lhs, const Date& rhs);

#endif //TODOLIST__DUETIME_H_
