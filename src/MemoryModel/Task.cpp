//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const DateTime &duedate) {
  if(name.empty()) throw std::invalid_argument("Task should be named.");
  this->name = name;
  this->label = label;
  this->priority = priority;
  this->due_date = duedate;
}

Task Task::create(const std::string &name, const std::string &label, Priority priority, const DateTime &duedate) {
  return Task(name, label, priority, duedate);
}

std::string Task::getName() const { return this->name; }

std::string Task::getLabel() const { return this->label; }

Priority Task::getPriority() const { return this->priority; }

DateTime Task::getDate() const { return this->due_date; }
