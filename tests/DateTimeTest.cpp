//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
#include "../src/MemoryModel/DateTime.h"

using testing::Eq;

class DateTimeTest : public testing::Test {

};

TEST_F(DateTimeTest, IncorrectYear) {
  EXPECT_THROW(DateTime(192, 10, 10, 10, 10), std::invalid_argument);
}

TEST_F(DateTimeTest, IncorrectMonth) {
  EXPECT_THROW(DateTime(2020, 0, 10, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 13, 10, 10, 10), std::invalid_argument);
}

TEST_F(DateTimeTest, IncorrectDay) {
  EXPECT_THROW(DateTime(2020, 1, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 2, 30, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2021, 2, 29, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 3, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 4, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 5, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 6, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 7, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 8, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 9, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 10, 32, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 11, 31, 10, 10), std::invalid_argument);
  EXPECT_THROW(DateTime(2020, 12, 32, 10, 10), std::invalid_argument);


  EXPECT_NO_THROW(DateTime(2020, 1, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 2, 29, 10, 10));
  EXPECT_NO_THROW(DateTime(2021, 2, 28, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 3, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 4, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 5, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 6, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 7, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 8, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 9, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2020,10, 31, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 11, 30, 10, 10));
  EXPECT_NO_THROW(DateTime(2020, 12, 31, 10, 10));
}

TEST_F(DateTimeTest, addWeek) {
  DateTime check(2020, 12, 28, 10, 10);
  EXPECT_NO_THROW(DateTime(addWeek(check)));

  ASSERT_EQ(2021, addWeek(check).getYear());
  ASSERT_EQ(1, addWeek(check).getMonth());
  ASSERT_EQ(4, addWeek(check).getDay());
}