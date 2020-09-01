//
// Created by rodion on 8/20/20.
//

#include <gtest/gtest.h>
#include <StateStorage.h>
#include <fstream>

class Base : public ::testing::Test {

};

TEST_F(Base, sss) {
/*  Context cont;
  cont.printState();
  cont.execute();*/

  StateStorage k;
  if(!k.execute()) {
    std::cout << "ERROR" << std::endl;
  }

/*  std::shared_ptr<StateInterface> k = std::make_shared<RemoveTaskState>();
  cont.changeState(k);
  cont.printState();*/
}