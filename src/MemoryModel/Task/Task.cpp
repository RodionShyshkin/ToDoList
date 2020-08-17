//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const Date &duedate) {
  if(name.empty()) throw std::invalid_argument("Task should be named.");
  this->name_ = name;
  this->label_ = label;
  this->priority_ = priority;
  this->due_date_ = duedate;
}

std::optional<Task> Task::create(const std::string &name, const std::string &label, Priority priority, const Date &duedate) {
  if(name == "" || label == "") return std::nullopt;
  return Task(name, label, priority, duedate);
}

std::string Task::GetName() const { return this->name_; }

std::string Task::GetLabel() const { return this->label_; }

Priority Task::GetPriority() const { return this->priority_; }

Date Task::GetDate() const { return this->due_date_; }
