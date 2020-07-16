//
// Created by rodion on 7/16/20.
//

#include "FullTask.h"

FullTask::FullTask() = default;

FullTask::FullTask(std::shared_ptr<Task> task) {
  this->setID();
  this->task = task;
}

std::shared_ptr<FullTask> FullTask::getRootTask() const { return rootTask; }

std::string FullTask::getRootTaskName() const {
  if(rootTask == NULL) return "NULL";
  return rootTask->task->getName();
}

std::vector<std::shared_ptr<FullTask>> FullTask::getSubtasks() const { return subtasks; }

void FullTask::pushSubtask(const FullTask &task) {
  auto subtask_ptr = std::make_shared<FullTask>(task);
  subtasks.push_back(subtask_ptr);
}

void FullTask::setRoot(std::shared_ptr<FullTask> root) {
  rootTask = root;
}

void FullTask::setID() {
  id = taskID::generateID();
}

unsigned int FullTask::getID() {
  return id;
}

void FullTask::showTask() {
  std::cout << "Task " << getID() << ": " << task->getName() << " (" << task->getLabel() << "), Priority: " << task->showPriority() << ". Deadline: " << task->getDate()
            << ". Root is " << getRootTaskName() << ". Subtasks number is " << getSubtasks().size() << ". Status: " << task->getStatus() << std::endl;
}