//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
#define TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_

#include <States/StateInterface.h>
#include <States/StateFactory.h>
#include <random>

class MainMenuState : public StateInterface {
 public:
  MainMenuState();

  bool                                input()                                   override;
  std::shared_ptr<StateInterface>     run(std::shared_ptr<Context> &context)    override;
  void                                output()                                  override;
  StateType                           getType()                                 override;

 private:
  Command                             command_;
};

#endif //TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
