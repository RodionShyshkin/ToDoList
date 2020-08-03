//
// Created by rodion on 7/21/20.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() = default;

TaskDTO::TaskDTO(const TaskEntity& task) : task(task) {}

TaskDTO::~TaskDTO() = default;

TaskID TaskDTO::getUserID() const { return task.getUserID(); }

std::string TaskDTO::getName() const { return task.getTask().getName(); }

std::string TaskDTO::getLabel() const { return task.getLabel(); }

Task::Priority TaskDTO::getPriority() const { return task.getPriority(); }

DueTime TaskDTO::getDueTime() const { return task.getDueTime(); }

bool TaskDTO::getStatus() const { return task.getStatus(); }

size_t TaskDTO::getSubtasksAmount() const { return task.getSubtasks().size(); }
