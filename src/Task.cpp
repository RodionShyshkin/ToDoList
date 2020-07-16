//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const std::string &name, const std::string &label, Priority priority, const DueTime &dueDate) {
  this->name = name;
  this->label = label;
  this->priority = priority;
  this->dueDate = dueDate;
  this->status = false;
}

Task::Task(const Task &task) : name(task.name), label(task.label), priority(task.priority), dueDate(task.dueDate), status(task.status) {}

Task::~Task() = default;

std::string Task::getName() const { return name; }

std::string Task::getLabel() const { return label; }

bool Task::getStatus() const { return status; }

Task::Priority Task::getPriority() const { return priority; }

DueTime Task::getDate() const { return dueDate; }

void Task::setStatus() { status = !status; }

std::string Task::showPriority() const {
  switch (priority) {
    case EMPTY: {
      return "No priority";
    }
    case LOW: {
      return "Low";
    }
    case MEDIUM: {
      return "Medium";
    }
    case HIGH: {
      return "High";
    }
    default: {
      return "Unknown priority";
    }
  }
}

/*void Task::showTask() const {
  std::cout << "Task " << getId() << ": " << getName() << " (" << getLabel() << "), Priority: " << convertPriority() << ". Deadline: " << getDate()
      << ". Root is " << getRootTaskName() << ". Subtasks number is " << getSubtasks().size() << ". Status: " << getStatus() << std::endl;
}*/

