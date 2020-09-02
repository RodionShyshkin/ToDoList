//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_

#include <States/StateInterface.h>

class NameParamState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::unique_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  bool  validateParam();

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_NAMEPARAMSTATE_H_
