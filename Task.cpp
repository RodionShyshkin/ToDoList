//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const int &dueDate) {
  this->name = name;
  this->label = label;
  this->priority = priority;
  this->dueDate = dueDate;
}

std::string Task::getName() { return name; }

std::string Task::getLabel() { return label; }

std::string Task::getPriority() {
  switch(priority) {
    case EMPTY: {
      return "No priority";
      break;
    }
    case LOW: {
     return "Low";
     break;
    }
    case MEDIUM: {
      return "Medium";
      break;
    }
    case HIGH: {
      return "High";
      break;
    }
  }
}

int Task::getDate() { return dueDate; }

