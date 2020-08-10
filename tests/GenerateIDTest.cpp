//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/GenerateID.h"

 class GenerateIDTest : public ::testing::Test {

};

TEST_F(GenerateIDTest, GenerateID) {
  GenerateID id;
  ASSERT_EQ(id.generateID(), 1);
  ASSERT_EQ(id.generateID(), 2);
}
