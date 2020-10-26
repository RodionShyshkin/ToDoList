//
// Created by Rodion Shyshkin on 26.10.2020.
//

#ifndef TODOLIST_TESTS_CLI_STATEFACTORYTEST_H_
#define TODOLIST_TESTS_CLI_STATEFACTORYTEST_H_

#include <gtest/gtest.h>
#include <States/StateFactory.h>

 class StateFactoryTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override) {

  }
};

TEST_F(StateFactoryTest, shouldReturnNullptrForUnknownState) {
  ASSERT_EQ(nullptr, StateFactory::create(StateType::UNKNOWN_STATE));
}

#endif //TODOLIST_TESTS_CLI_STATEFACTORYTEST_H_
