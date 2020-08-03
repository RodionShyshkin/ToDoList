//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
#include "DateTime.h"

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