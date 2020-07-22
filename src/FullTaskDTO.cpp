//
// Created by rodion on 7/21/20.
//

#include "FullTaskDTO.h"

FullTaskDTO::FullTaskDTO(std::shared_ptr<FullTask> task) : task(task) {}

FullTaskDTO::~FullTaskDTO() = default;

TaskID FullTaskDTO::getID() const { return task->getUserID(); }

std::string FullTaskDTO::getName() const { return task->getTask().getName(); }

std::string FullTaskDTO::getLabel() const { return task->getLabel(); }

Task::Priority FullTaskDTO::getPriority() const { return task->getPriority(); }

DueTime FullTaskDTO::getDueTime() const { return task->getTime(); }

bool FullTaskDTO::getStatus() const { return task->getStatus(); }

