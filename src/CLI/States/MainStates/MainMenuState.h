//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
#define TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_

#include <States/StateFactory.h>
#include <AvailableCommands.h>

class MainMenuState : public StateInterface {
 public:
  StateResult       run(std::shared_ptr<Context> &context)          override;
  StateType         getType()                                       override;

 private:
  bool              input(const std::shared_ptr<IOInterface> &io_)  override;
  void              output(const std::shared_ptr<IOInterface> &io_) override;

 private:
  Command                             command_;
};

#endif //TODOLIST_SRC_CLI_STATES_MAINMENUSTATE_H_
