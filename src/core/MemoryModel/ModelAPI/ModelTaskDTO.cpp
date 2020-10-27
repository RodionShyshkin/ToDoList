//
// Created by rodion on 9/29/20.
//

#include "ModelTaskDTO.h"

ModelTaskDTO::ModelTaskDTO() = default;

ModelTaskDTO ModelTaskDTO::CreateWithParent(const TaskID &id,
                                            const std::string &name,
                                            const std::string &label,
                                            const Priority &priority,
                                            const Date &date,
                                            const bool &status,
                                            const TaskID& parent) {
  return ModelTaskDTO{id, name, label, priority, date, status, parent};
}

ModelTaskDTO ModelTaskDTO::CreateWithoutParent(const TaskID &id,
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

TaskID ModelTaskDTO::GetID() const { return task_id_; }

std::string ModelTaskDTO::GetName() const { return task_name_; }

std::string ModelTaskDTO::GetLabel() const { return task_label_; }

Priority ModelTaskDTO::GetPriority() const { return task_priority_; }

Date ModelTaskDTO::GetDueDate() const { return task_due_date_; }

bool ModelTaskDTO::GetStatus() const { return task_status_; }

TaskID ModelTaskDTO::GetParentID() const { return parent_id_; }