//
// Created by rodion on 7/15/20.
//

#include "Task.h"

Task::Task() = default;

Task::Task(const unsigned int &id, const std::string &name, const std::string &label, Priority priority, const int &dueDate) {
  this->id = id;
  this->name = name;
  this->label = label;
  this->priority = priority;
  this->dueDate = dueDate;
  this->status = false;
  this->rootTask = NULL;
}

Task::Task(const Task &task) : name(task.name), label(task.label), priority(task.priority), dueDate(task.dueDate), status(task.status), rootTask(task.rootTask), id(task.id) {}

Task::~Task() = default;

unsigned int Task::getId() const { return id; }

std::string Task::getName() const { return name; }

std::string Task::getLabel() const { return label; }

Priority Task::getPriority() const { return priority; }

int Task::getDate() const { return dueDate; }

std::shared_ptr<Task> Task::getRootTask() const { return rootTask; }

std::string Task::getRootTaskName() const {
  if(rootTask == NULL) return "NULL";
  return rootTask->getName();
}

std::vector<std::shared_ptr<Task> > Task::getSubtasks() const { return subtasks; }

void Task::setStatus() { status = !status; }

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
  std::cout << "Task " << getId() << ": " << getName() << " (" << getLabel() << "), Priority: " << convertPriority() << ". Deadline: " << getDate()
      << ". Root is " << getRootTaskName() << ". Subtasks number is " << getSubtasks().size() << std::endl;
}

void Task::pushSubtask(const Task &task) {
  auto subtask_ptr = std::make_shared<Task>(task);
  subtasks.push_back(subtask_ptr);
  std::cout << subtasks.size() << std::endl;
  std::cout << this->getSubtasks().size() << std::endl;
}

void Task::setRoot(std::shared_ptr<Task> root) {
  rootTask = root;
}