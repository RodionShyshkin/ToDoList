//
// Created by rodion on 8/20/20.
//

#include <gtest/gtest.h>
#include <Context.h>

 class Base : public ::testing::Test {

};

TEST_F(Base, sss) {
/*  Context cont;
  cont.printState();
  cont.execute();*/

  StateStorage k;
  k.execute();



/*  std::shared_ptr<StateInterface> k = std::make_shared<RemoveTaskState>();
  cont.changeState(k);
  cont.printState();*/
}