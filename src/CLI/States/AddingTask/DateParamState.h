//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_

#include <States/StateInterface.h>
#include <boost/date_time/gregorian/parsers.hpp>

class DateParamState : public StateInterface {
 public:
  StateResult                   run(std::shared_ptr<Context> &context)            override;
  StateType                     getType()                                         override;

 private:
  bool                          input(const std::shared_ptr<IOInterface> &io_)    override;
  void                          output(const std::shared_ptr<IOInterface> &io_)   override;

  static std::optional
  <boost::gregorian::date>      parseParam(const std::string&);

 private:
  boost::gregorian::date        param_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_DATEPARAMSTATE_H_
