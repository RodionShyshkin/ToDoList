//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskManager.h"
#include "TaskOutput.h"

using Pointer = std::shared_ptr<FullTask>;
using Vector = std::vector<FullTaskDTO>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskManager::TaskManager() : newID() {}
TaskManager::~TaskManager() = default;


void TaskManager::showAllTasks() const {
  if (sortedTasks.empty()) { std::cout << "No tasks" << std::endl; }
  else {
    for (auto[key, value] : sortedTasks) {
      TaskOutput::printTask(value);
    }
  }
}

void TaskManager::showTasksForToday() const {
  if(sortedTasks.empty()) { std::cout << "no tasks" << std::endl; }
  else {
    std::vector<FullTaskDTO> todayTasks;
    for(auto [priority, task] : sortedTasks) {
      auto now = getCurrentTime();
      auto taskDate = task.getDueTime().getTime();

      if(now.getYear() == taskDate.getYear() && now.getMonth() == taskDate.getMonth() && now.getDay() == taskDate.getDay()) {
        todayTasks.push_back(task);
      }
    }
    if(todayTasks.empty()) { std::cout << "There are no tasks for today." << std::endl; }
    else {
      for(auto todayTask : todayTasks) { TaskOutput::printTask(todayTask); }
    }
  }
}

/*void TaskManager::showTasksForWeek() const {
  if(sortedTasks.empty()) { std::cout << "no tasks" << std::endl; }
  else {
    std::vector<FullTask> weekTasks;
    for(auto [priority, task] : sortedTasks) {
      auto now = getCurrentTime();
      auto taskDate = task->getTime().getTime();


    }
  }
}*/

void TaskManager::showTasksForLabel(const std::string &label) const {
  Vector searchResult;
  for (auto[priority, sortingTask] : sortedTasks) {
    if (sortingTask.getLabel() == label) {
      searchResult.push_back(sortingTask);
    }
  }
  if (searchResult.size() == 0) std::cout << "No tasks found." << std::endl;
  else {
    std::cout << searchResult.size() << " tasks found." << std::endl;
    for (auto itemTask : searchResult) TaskOutput::printTask(itemTask);
  }
}

void TaskManager::addTask(const Task &task) {
  auto task_ptr = std::make_shared<FullTask>(task, newID.generateID());
  tasks.push_back(task_ptr);
  sortedTasks.insert(std::pair<Task::Priority, std::shared_ptr<FullTask>>(task.getPriority(), task_ptr));
}

void TaskManager::addSubtask(const TaskID &id, const Task &subtask) {
  for (auto task : tasks) {
    if (task.getUserID() == id) {
      auto subptr = std::make_shared<FullTask>(subtask, id);
      task.AddSubtask(subptr);
      addTask(subtask);
      return;
    }
  }
}

void TaskManager::removeTask(const TaskID &id) {
  auto taskToRemove = FullTaskDTO(); //std::make_shared<FullTaskDTO>();
  size_t NumInVector;
  auto IteratorInMultimap = sortedTasks.begin();

  for (auto counter = 0; counter < tasks.size(); counter++) {
    if (tasks[counter].getUserID() == id) {
      taskToRemove = tasks[counter];
      NumInVector = counter;
      break;
    }
  }
  for (auto it = sortedTasks.begin(); it != sortedTasks.end(); ++it) {
    if (it->second.getUserID() == id) {
      IteratorInMultimap = it;
      break;
    }
  }

  tasks.erase(tasks.begin() + NumInVector);
  sortedTasks.erase(IteratorInMultimap);
}

void TaskManager::completeTask(const TaskID &id) {
  for(auto task : tasks) {
    if(task.getUserID() == id) {
      task.setComplete();
      return;
    }
  }
}

void TaskManager::postponeTask(const TaskID &id, const DateTime &newtime) {
  for(auto task : tasks) {
    if(task.getUserID() == id) {
      auto newtask = Task(task.getName(), task.getLabel(), task.getPriority(), newtime);
      task.postponeTask(newtask);
   }
  }
}

