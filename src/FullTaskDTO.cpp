//
// Created by rodion on 7/21/20.
//

#include "FullTaskDTO.h"

FullTaskDTO::FullTaskDTO() = default;

FullTaskDTO::FullTaskDTO(std::shared_ptr<FullTask> task) : task(task) {}

FullTaskDTO::~FullTaskDTO() = default;

TaskID FullTaskDTO::getUserID() const { return task->getUserID(); }

std::string FullTaskDTO::getName() const { return task->getTask().getName(); }

std::string FullTaskDTO::getLabel() const { return task->getLabel(); }

Task::Priority FullTaskDTO::getPriority() const { return task->getPriority(); }

DueTime FullTaskDTO::getDueTime() const { return task->getTime(); }

bool FullTaskDTO::getStatus() const { return task->getStatus(); }

size_t FullTaskDTO::getSubtasksAmount() const { return task->getSubtasks().size(); }

void FullTaskDTO::AddSubtask(const std::shared_ptr<FullTask> &subtask) { task->AddSubtask(subtask); }

void FullTaskDTO::setComplete() {
  task->setComplete();
}

void FullTaskDTO::postponeTask(const Task &newtask) {
  task->postponeTask(newtask);
}
