//
// Created by rodion on 8/28/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTCONTEXT_H_
#define TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTCONTEXT_H_

#include <string>
#include <ListModifier.h>
#include <boost/date_time/gregorian/greg_date.hpp>

class ShowListContext {
 public:
  ShowListContext();

 public:
  ListModifier  getModifier() const;
  bool          getSorted() const;

 public:
  void updateContext(const ListModifier& modifier, const bool& is_sorted);

 private:
  ListModifier modifier_;
  bool is_sorted_;
};

#endif //TODOLIST_SRC_CLI_STATES_SHOWTASKSLIST_SHOWLISTCONTEXT_H_
