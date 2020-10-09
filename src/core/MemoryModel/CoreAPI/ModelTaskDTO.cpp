//
// Created by rodion on 9/29/20.
//

#include "ModelTaskDTO.h"

ModelTaskDTO::ModelTaskDTO() = default;

ModelTaskDTO ModelTaskDTO::createWithParent(const TaskID &id,
                                  const std::string &name,
                                  const std::string &label,
                                  const Priority &priority,
                                  const Date &date,
                                  const bool &status,
                                  const TaskID& parent) {
  return ModelTaskDTO{id, name, label, priority, date, status, parent};
}

ModelTaskDTO ModelTaskDTO::createWithoutParent(const TaskID &id,
                                            const std::string &name,
                                            const std::string &label,
                                            const Priority &priority,
                                            const Date &date,
                                            const bool &status) {
  return ModelTaskDTO{id, name, label, priority, date, status, id};
}

ModelTaskDTO::ModelTaskDTO(const TaskID &id,
                           const std::string &name,
                           const std::string &label,
                           const Priority &priority,
                           const Date &date,
                           const bool &status,
                           const TaskID& parent) {
  this->task_id_ = id;
  this->task_name_ = name;
  this->task_label_ = label;
  this->task_priority_ = priority;
  this->task_due_date_ = date;
  this->task_status_ = status;
  this->parent_id_ = parent;
}

TaskID ModelTaskDTO::getID() const { return this->task_id_; }

std::string ModelTaskDTO::getName() const { return this->task_name_; }

std::string ModelTaskDTO::getLabel() const { return this->task_label_; }

Priority ModelTaskDTO::getPriority() const { return this->task_priority_; }

Date ModelTaskDTO::getDueDate() const { return this->task_due_date_; }

bool ModelTaskDTO::getStatus() const { return this->task_status_; }

TaskID ModelTaskDTO::getParentID() const { return this->parent_id_; }