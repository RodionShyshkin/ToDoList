//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
#include "DueTime.h"

using testing::Eq;

class DateTimeTest : public testing::Test {

};

TEST_F(DateTimeTest, IncorrectYear) {
  EXPECT_THROW(DateTime(192, 10, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(0, 10, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(-100, 10, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(1899, 12, 9, 23, 59), std::invalid_argument);
  EXPECT_THROW(DateTime(2101, 1, 1, 0, 0), std::invalid_argument);
}

TEST_F(DateTimeTest, IncorrectMonth) {
  EXPECT_THROW(DateTime(2020, -5, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 0, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 13, 10, 10, 10), std::invalid_argument);
}

TEST_F(DateTimeTest, IncorrectDay) {
  EXPECT_THROW(DateTime(2020, 1, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2018, 2, 30, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2021, 2, 29, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2008, 3, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2029, 4, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(1994, 5, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(1917, 6, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(1999, 7, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2000, 8, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2001, 9, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2004, 10, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2006, 11, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2026, 12, 32, 10, 10), std::invalid_argument);
}

TEST_F(DateTimeTest, CorrectDay) {
  EXPECT_NO_THROW(DateTime(1984, 1, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2028, 2, 29, 10, 10));
  EXPECT_NO_THROW(DateTime(2035, 2, 28, 10, 10));
  EXPECT_NO_THROW(DateTime(2044, 3, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2002, 4, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 5, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2030, 6, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2000, 7, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(1972, 8, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(1962, 9, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(1941,10, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(1945, 11, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(1900, 12, 31, 10, 10));
}

TEST_F(DateTimeTest, addWeek) {
  DateTime check(2020, 12, 28, 10, 10);
  EXPECT_NO_THROW(DateTime(addWeek(check)));

  ASSERT_EQ(2021, addWeek(check).getYear());
  ASSERT_EQ(1, addWeek(check).getMonth());
  ASSERT_EQ(4, addWeek(check).getDay());
}

TEST_F(DateTimeTest, getCurrentTime) {
  auto check = getCurrentTime();

  time_t t = time(0);
  struct tm * now = localtime(&t);

  ASSERT_EQ(now->tm_year + 1900, check.getYear());
  ASSERT_EQ(now->tm_mon + 1, check.getMonth());
  ASSERT_EQ(now->tm_mday, check.getDay());
  ASSERT_EQ(now->tm_hour, check.getHours());
  ASSERT_EQ(now->tm_min, check.getMinutes());
}

TEST_F(DateTimeTest, copyConstructor) {
  tm time = {11, 12, 13, 8, 0, 34};
  auto check = DateTime(time);

  ASSERT_EQ(check.getYear(), 1934);
  ASSERT_EQ(check.getMonth(), 1);
  ASSERT_EQ(check.getDay(), 8);
  ASSERT_EQ(check.getHours(), 13);
  ASSERT_EQ(check.getMinutes(), 12);
}

TEST_F(DateTimeTest, lessOperator) {
  auto lhs = DueTime(DateTime(1934, 2, 8, 13, 12));
  auto rhs = DueTime(DateTime(1933, 2, 8, 13, 12));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1934, 1, 8, 13, 12));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1934, 2, 7, 13, 12));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1934, 2, 8, 12, 12));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1934, 2, 8, 13, 11));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1933, 1, 7, 12, 11));
  ASSERT_EQ(true, lhs > rhs);

  rhs = DueTime(DateTime(1934, 2, 8, 13, 12));
  ASSERT_EQ(false, lhs > rhs);

  rhs = DueTime(DateTime(1934, 3, 8, 13, 12));
  ASSERT_EQ(false, lhs > rhs);

  rhs = DueTime(DateTime(1935, 2, 8, 13, 12));
  ASSERT_EQ(false, lhs > rhs);
}

TEST_F(DateTimeTest, getTime) {
  auto date_time = DateTime(1934, 2, 8, 13, 12);
  auto due_time = DueTime(date_time);

  ASSERT_EQ(due_time.getTime(), date_time);
}