//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_

#include <States/StateInterface.h>
#include <AvailableCommands.h>

class ViewTaskState : public StateInterface {
 public:
  ViewTaskState();

 public:
  StateResult         run(std::shared_ptr<Context> context)             override;
  StateType           getType()                                         override;
  std::unique_ptr
  <StateInterface>    switchState()                                     override;

 private:
  bool                input(const std::shared_ptr<IOInterface> &io_)    override;
  void                output(const std::shared_ptr<IOInterface> &io_)   override;

  static void         showTask(const TaskDTO&, const std::shared_ptr<IOInterface>&);

 private:
  Command             command_;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKSTATE_H_