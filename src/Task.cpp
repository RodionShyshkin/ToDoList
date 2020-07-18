//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const DueTime &duetime) {
  this->name = name;
  this->label = label;
  this->priority = priority;
  this->duetime = duetime;
}

Task::Task(const Task &task) : name(task.name), label(task.label), priority(task.priority), duetime(task.duetime) {}

Task::~Task() = default;

std::string Task::getName() const { return name; }

std::string Task::getLabel() const { return label; }

Task::Priority Task::getPriority() const { return priority; }

DueTime Task::getDate() const { return duetime; }
