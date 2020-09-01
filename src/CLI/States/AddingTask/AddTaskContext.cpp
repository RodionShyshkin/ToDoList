//
// Created by rodion on 8/27/20.
//

#include "AddTaskContext.h"

AddTaskContext::AddTaskContext() {
  updateContext("", "", Priority::EMPTY, this->getDate(), 0);
}

void AddTaskContext::updateContext(const std::string& name,
                                   const std::string& label,
                                   const Priority& priority,
                                   const boost::gregorian::date& date,
                                   const unsigned int& parent_id) {
  this->name_ = name;
  this->label_ = label;
  this->priority_ = priority;
  this->date_ = date;
  this->parent_id_ = parent_id;
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

unsigned int AddTaskContext::getParent() const {
  return parent_id_;
}