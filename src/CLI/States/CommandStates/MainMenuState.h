//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
#define TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_

#include <States/StateInterface.h>
#include <Commands/Command.h>

class MainMenuState : public StateInterface {
 public:
  MainMenuState();

 public:
  StateResult                      run(std::shared_ptr<Context> context)  override;
  StateType                        getType()                              override;
  std::unique_ptr<StateInterface>  switchState()                          override;

 private:
  bool              input(const std::shared_ptr<IOInterface> &io)  override;
  void              output(const std::shared_ptr<IOInterface> &io) override;

 private:
  Command                             command_;
};

#endif //TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
