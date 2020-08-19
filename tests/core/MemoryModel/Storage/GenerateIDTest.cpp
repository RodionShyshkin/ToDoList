//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Storage/IDGenerator.h"

 class GenerateIDTest : public ::testing::Test {

};

TEST_F(GenerateIDTest, GenerateID) {
  IDGenerator id;
  ASSERT_EQ(id.GenerateID(), 1);
  ASSERT_EQ(id.GenerateID(), 2);
}
