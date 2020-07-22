//
// Created by rodion on 7/21/20.
//

#include "TaskOutput.h"
#include <iostream>

std::string PriorityToString(Task::Priority priority) {
 switch(priority) {
   case Task::EMPTY:
     return "No priority";
   case Task::LOW:
     return "Low";
   case Task::MEDIUM:
     return "Medium";
   case Task::HIGH:
     return "High";
 }
 return "Unknown value";
}

std::string StatusToString(bool status) {
  if(status) return "Completed"; else return "Not completed";
}
