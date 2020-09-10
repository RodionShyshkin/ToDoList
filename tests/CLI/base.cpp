//
// Created by rodion on 8/20/20.
//

#include <gtest/gtest.h>
#include <StateMachine.h>
#include <fstream>
#include <States/MainStates/MainMenuState.h>

class Base : public ::testing::Test {

};

TEST_F(Base, sss) {
/*  Context cont;
  cont.printState();
  cont.execute();*/


//  auto k = StateMachine<Context, StateInterface, MainMenuState>::create(StatesGraphType::MAIN);\

  std::shared_ptr<Context> context = std::make_shared<Context>();
  StateMachine k = StateMachine::create(StatesGraphType::MAIN, context);
  if(!k.execute()) {
    std::cout << "ERROR" << std::endl;
  }

/*  std::shared_ptr<StateInterface> k = std::make_shared<RemoveTaskState>();
  cont.changeState(k);
  cont.printState();*/
}