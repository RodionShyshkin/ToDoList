//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_

#include <States/StateInterface.h>

class DateParamState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::unique_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  std::optional<boost::gregorian::date> parseParam() const;

 private:
  std::string param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
