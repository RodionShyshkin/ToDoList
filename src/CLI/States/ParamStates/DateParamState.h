//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_

#include <States/StateInterface.h>
#include <boost/date_time/gregorian/parsers.hpp>

class DateParamState : public StateInterface {
 public:
  StateResult                   run(std::shared_ptr<Context> context)            override;
  StateType                     getType() const                                  override;
  std::unique_ptr<StateInterface> switchState() override;

 public:
  bool                          input(const std::shared_ptr<IOInterface> &io)    override;
  void                          output(const std::shared_ptr<IOInterface> &io)   override;

 private:
  boost::gregorian::date        param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
