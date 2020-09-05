//
// Created by rodion on 9/5/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_NEWDATEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_NEWDATEPARAMSTATE_H_

#include <StateInterface.h>
#include <boost/date_time/gregorian/gregorian.hpp>

class NewDateParamState : public StateInterface {
 public:
  bool input() override;
  std::shared_ptr<StateInterface> run(std::unique_ptr<Context> &context) override;
  void output() override;
  StateType getType() override;

 private:
  std::optional<boost::gregorian::date> parseParam() const;

 private:
  std::string param_;
  unsigned int task_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_NEWDATEPARAMSTATE_H_
