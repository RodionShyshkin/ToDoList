//
// Created by rodion on 7/21/20.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() = default;

TaskDTO::TaskDTO(const unsigned int& id,
                 const std::string &name,
                 const std::string &label,
                 const Priority &priority,
                 const boost::gregorian::date &date,
                 const bool& status) {
  this->task_id_ = id;
  this->task_name_ = name;
  this->task_label_ = label;
  this->task_priority_ = priority;
  this->task_due_date_ = date;
  this->task_status_ = status;
}

TaskDTO TaskDTO::create(const unsigned int& id,
                        const std::string &name,
                        const std::string &label,
                        const Priority &priority,
                        const boost::gregorian::date &date,
                        const bool& status) {
  return TaskDTO{id, name, label, priority, date, status};
}

unsigned int TaskDTO::getID() const { return this->task_id_; }

std::string TaskDTO::getName() const { return this->task_name_; }

std::string TaskDTO::getLabel() const { return this->task_label_; }

Priority TaskDTO::getPriority() const { return this->task_priority_; }

boost::gregorian::date TaskDTO::getDueDate() const { return this->task_due_date_; }

bool TaskDTO::getStatus() const { return this->task_status_; }
