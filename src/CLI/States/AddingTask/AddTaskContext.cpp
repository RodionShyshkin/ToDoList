//
// Created by rodion on 8/27/20.
//

#include "AddTaskContext.h"

AddTaskContext::AddTaskContext() {
  updateContext("", "", Priority::EMPTY, this->getDate());
}

void AddTaskContext::updateContext(std::string name, std::string label, Priority priority, boost::gregorian::date date) {
  this->name_ = name;
  this->label_ = label;
  this->priority_ = priority;
  this->date_ = date;
}

std::string AddTaskContext::getName() const {
  return name_;
}

std::string AddTaskContext::getLabel() const {
  return label_;
}

Priority AddTaskContext::getPriority() const {
  return priority_;
}

boost::gregorian::date AddTaskContext::getDate() const {
  return date_;
}