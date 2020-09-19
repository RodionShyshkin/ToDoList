//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
#define TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_

#include <States/StateInterface.h>
#include <States/StateFactory.h>
#include <random>
#include <gtest/gtest_prod.h>

class MainMenuState : public StateInterface {
 public:
  std::shared_ptr<StateInterface>     run(std::shared_ptr<Context> &context)          override;
  StateType                           getType()                                       override;

 private:
  bool                                input(const std::shared_ptr<IOInterface> &io_)  override;
  void                                output(const std::shared_ptr<IOInterface> &io_) override;

  FRIEND_TEST(MainMenuTest, rightInput);

 private:
  Command                             command_;
};

#endif //TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
