//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "DueTime.h"

using testing::Eq;

class DueTimeTest : public testing::Test {

};

TEST_F(DueTimeTest, shouldConvertIntsToTime) {
  DueTime time(2020, 07, 14, 10, 45, 21);
  ASSERT_EQ(2020, time.getYear());
  ASSERT_EQ(07, time.getMonth());
  ASSERT_EQ(14, time.getDay());
  ASSERT_EQ(10, time.getHours());
  ASSERT_EQ(45, time.getMinutes());
  ASSERT_EQ(21, time.getSeconds());

//  ASSERT_EQ(false, task.getStatus());
}
