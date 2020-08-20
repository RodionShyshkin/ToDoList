//
// Created by rodion on 8/20/20.
//

#include <gtest/gtest.h>
#include <Context.h>

 class Base : public ::testing::Test {

};

TEST_F(Base, sss) {
  Context cont;
  cont.readState();
  cont.execute();
}