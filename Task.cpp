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
  this->status = false;
}

std::string Task::getName() const { return name; }

std::string Task::getLabel() const { return label; }

Priority Task::getPriority() const { return priority; }

int Task::getDate() const { return dueDate; }

std::string Task::convertPriority() const {
  switch (priority) {
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

void Task::showTask() const {
  std::cout << "Task: " << getName() << " (" << getLabel() << "), Priority: " << convertPriority() << ". Deadline: " << getDate() << std::endl;
}