//
// Created by rodion on 10/24/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_PARAMSTATES_FILENAMEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_PARAMSTATES_FILENAMEPARAMSTATE_H_

#include <States/StateInterface.h>

class FilenameParamState : public StateInterface {
 public:
  StateResult run(std::shared_ptr<Context> context) override;
  StateType getType() override;
  std::unique_ptr<StateInterface> switchState() override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

 private:
  std::string filename_;
};

#endif //TODOLIST_SRC_CLI_STATES_PARAMSTATES_FILENAMEPARAMSTATE_H_
