//
// Created by rodion on 8/27/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKCONTEXT_H_
#define TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKCONTEXT_H_

#include <string>
#include <API/Priority.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <ContextInterface.h>

class AddTaskContext : public ContextInterface {
 public:
  AddTaskContext();

 public:
  std::string getName() const;
  std::string getLabel() const;
  Priority getPriority() const;
  boost::gregorian::date getDate() const;
  unsigned int getParent() const;

 public:
  void updateContext(const std::string& name, const std::string& label, const Priority& priority,
                     const boost::gregorian::date&, const unsigned int&);

 private:
  std::string name_;
  std::string label_;
  Priority priority_;
  boost::gregorian::date date_;
  unsigned int parent_id_;
};

#endif //TODOLIST_SRC_CLI_STATES_ADDINGTASK_ADDTASKCONTEXT_H_
