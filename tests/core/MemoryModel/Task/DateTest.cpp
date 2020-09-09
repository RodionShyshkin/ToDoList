//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Task/Date.h"

 class DateTest : public ::testing::Test {

};

TEST_F(DateTest, gettingDate) {
  boost::gregorian::date date(boost::gregorian::greg_year(2001), boost::gregorian::greg_month(9),
                              boost::gregorian::greg_day(11));
  Date date_time(date);
  auto check = date_time.GetDate();
  ASSERT_EQ(check.day(), 11);
  ASSERT_EQ(check.year(), 2001);
  ASSERT_EQ(check.month(), 9);
}

TEST_F(DateTest, BoostConstructor) {
  EXPECT_NO_THROW(Date(boost::gregorian::date(boost::gregorian::date(boost::gregorian::greg_year(1991),
                                                                     boost::gregorian::greg_month(8), boost::gregorian::greg_day(23)))));

}

TEST_F(DateTest, IntConstructor) {
  auto check = Date(1986, 9, 26);
  ASSERT_EQ(check.GetDate().year(), 1986);
  ASSERT_EQ(check.GetDate().month(), 9);
  ASSERT_EQ(check.GetDate().day(), 26);
}

TEST_F(DateTest, lessOperator) {
  auto lhs = Date(2021, 8, 6);
  auto mhs = Date(2021, 8, 7);
  auto mhs_clone = Date(2021, 8, 7);
  auto rhs = Date(2021, 8, 5);
  ASSERT_TRUE(lhs < mhs);
  ASSERT_FALSE(mhs < mhs_clone);
  ASSERT_FALSE(mhs < rhs);
}

TEST_F(DateTest, currentDate) {
  EXPECT_NO_THROW(Date::GetCurrentDate());
}

TEST_F(DateTest, checkWeek) {
  auto first_point = Date(2050, 9, 6);
  auto second_point = Date(2050, 9, 7);
  auto third_point = Date(2050, 9, 8);
  ASSERT_FALSE(Date::CheckWeek(first_point));
  ASSERT_FALSE(Date::CheckWeek(second_point));
  ASSERT_FALSE(Date::CheckWeek(third_point));

  auto fourth_point = Date(2020, 9, 13);

  ASSERT_TRUE(Date::CheckWeek(fourth_point));
}
