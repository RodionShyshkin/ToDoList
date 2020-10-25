//
// Created by Rodion Shyshkin on 25.10.2020.
//

#include <gtest/gtest.h>
#include <API/Priority.h>

 class PriorityTest : public ::testing::Test {

};

TEST_F(PriorityTest, getStringByPriority) {
  ASSERT_EQ("Empty", stringByPriority(Priority::EMPTY));
  ASSERT_EQ("Low", stringByPriority(Priority::LOW));
  ASSERT_EQ("Medium", stringByPriority(Priority::MEDIUM));
  ASSERT_EQ("High", stringByPriority(Priority::HIGH));
}