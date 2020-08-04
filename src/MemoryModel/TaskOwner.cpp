//
// Created by rodion on 8/2/20.
//

#include "TaskOwner.h"

TaskOwner::TaskOwner() : newID(GenerateID()) {}

TaskOwner::~TaskOwner() = default;

TaskID TaskOwner::generateID() { return newID.generateID(); }

void TaskOwner::pushTask(const std::pair<TaskID, std::shared_ptr<TaskEntity> >& task) {
  tasks.insert(task);
}

bool TaskOwner::if_exist(const TaskID &id) {
  if(tasks.find(id) != tasks.end()) return true; else return false;
}
