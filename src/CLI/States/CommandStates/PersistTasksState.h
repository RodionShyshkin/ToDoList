//
// Created by rodion on 10/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_PERSISTTASKSSTATE_H_
#define TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_PERSISTTASKSSTATE_H_

#include <States/StateInterface.h>

enum class PersistType {
  SAVE,
  LOAD
};

class PersistTasksState : public StateInterface {
 public:
  PersistTasksState(const PersistType& type);

 public:
  StateResult       run(std::shared_ptr<Context> context) override;
  StateType         getType() override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool              input(const std::shared_ptr<IOInterface> &io) override;
  void              output(const std::shared_ptr<IOInterface> &io) override;

 private:
  PersistType       type_;
};

#endif //TODOLIST_SRC_CLI_STATES_SAVELOADSTATES_PERSISTTASKSSTATE_H_
