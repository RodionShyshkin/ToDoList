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
  task_id_ = id;
  task_name_ = name;
  task_label_ = label;
  task_priority_ = priority;
  task_due_date_ = date;
  task_status_ = status;
  parent_id_ = parent;
}

TaskID ModelTaskDTO::getID() const { return task_id_; }

std::string ModelTaskDTO::getName() const { return task_name_; }

std::string ModelTaskDTO::getLabel() const { return task_label_; }

Priority ModelTaskDTO::getPriority() const { return task_priority_; }

Date ModelTaskDTO::getDueDate() const { return task_due_date_; }

bool ModelTaskDTO::getStatus() const { return task_status_; }

TaskID ModelTaskDTO::getParentID() const { return parent_id_; }