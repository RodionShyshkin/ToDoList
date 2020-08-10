//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/DateTime.h"

 class DateTimeTest : public ::testing::Test {

};

TEST_F(DateTimeTest, gettingDate) {
  boost::gregorian::date date(boost::gregorian::greg_year(2001), boost::gregorian::greg_month(9),
                              boost::gregorian::greg_day(11));
  DateTime date_time(date);
  auto check = date_time.get_date();
  ASSERT_EQ(check.day(), 11);
  ASSERT_EQ(check.year(), 2001);
  ASSERT_EQ(check.month(), 9);
}

TEST_F(DateTimeTest, BoostConstructor) {
  EXPECT_NO_THROW(DateTime(boost::gregorian::date(boost::gregorian::date(boost::gregorian::greg_year(1991),
                           boost::gregorian::greg_month(8),boost::gregorian::greg_day(23)))));

}

TEST_F(DateTimeTest, IntConstructor) {
  auto check = DateTime(1986, 9, 26);
  ASSERT_EQ(check.get_date().year(), 1986);
  ASSERT_EQ(check.get_date().month(), 9);
  ASSERT_EQ(check.get_date().day(), 26);
}

TEST_F(DateTimeTest, lessOperator) {
  auto lhs = DateTime(2021, 8, 6);
  auto mhs = DateTime(2021, 8, 7);
  auto mhs_clone = DateTime(2021, 8, 7);
  auto rhs = DateTime(2021, 8, 5);
  ASSERT_TRUE(lhs < mhs);
  ASSERT_FALSE(mhs < mhs_clone);
  ASSERT_FALSE(mhs < rhs);
}

TEST_F(DateTimeTest, currentDate) {
  EXPECT_NO_THROW(DateTime::get_current_date());
}

TEST_F(DateTimeTest, checkWeek) {
  auto first_point = DateTime(2050, 9, 6);
  auto second_point = DateTime(2050, 9, 7);
  auto third_point = DateTime(2050, 9, 8);
  ASSERT_FALSE(checkWeek(first_point));
  ASSERT_FALSE(checkWeek(second_point));
  ASSERT_FALSE(checkWeek(third_point));
}
