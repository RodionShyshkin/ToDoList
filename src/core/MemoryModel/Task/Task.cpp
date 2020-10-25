//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const Date &duedate) :
name_(name), label_(label), priority_(priority), due_date_(duedate) { }

std::optional<Task> Task::create(const std::string &name, const std::string &label, Priority priority, const Date &duedate) {
  if(name == "") return std::nullopt;
  return Task(name, label, priority, duedate);
}

std::string Task::GetName() const { return name_; }

std::string Task::GetLabel() const { return label_; }

Priority Task::GetPriority() const { return priority_; }

Date Task::GetDate() const { return due_date_; }
