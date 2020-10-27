//
// Created by rodion on 8/21/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
#define TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_

#include <States/StateInterface.h>
#include <Commands/Command.h>

class ViewTaskListState : public StateInterface {
 public:
  ViewTaskListState();

 public:
  StateResult     run(std::shared_ptr<Context> context)             override;
  StateType       getType() const                                  override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool            input(const std::shared_ptr<IOInterface> &io)    override;
  void            output(const std::shared_ptr<IOInterface> &io)   override;

  static void     showList(const std::vector<TaskDTO>&, const std::shared_ptr<IOInterface>&);

  Command         command_;
};

#endif //TODOLIST_SRC_CLI_STATES_VIEWTASKLISTSTATE_H_
