//
// Created by rodion on 9/15/20.
//

#include <string>
#include "Priority.h"

std::string stringByPriority(const Priority& priority) {
  if(priority == Priority::EMPTY) return "Empty";
  else if(priority == Priority::LOW) return "Low";
  else if(priority == Priority::MEDIUM) return "Medium";
  else if(priority == Priority::HIGH) return "High";
  else return "";
}
