//
// Created by rodion on 10/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_SAVETASKSSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_SAVETASKSSTATE_H_

#include <States/StateInterface.h>

enum class PersisterType {
  SAVE,
  LOAD
};

class SaveTasksState : public StateInterface {
 public:
  SaveTasksState(const PersisterType& type);

 public:
  StateResult run(std::shared_ptr<Context> &context) override;
  StateType getType() override;

 private:
  bool input(const std::shared_ptr<IOInterface> &io_) override;
  void output(const std::shared_ptr<IOInterface> &io_) override;

 private:
  std::string filepath_;
  PersisterType type_;
};

#endif //TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_SAVETASKSSTATE_H_
