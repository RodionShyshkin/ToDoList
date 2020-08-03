//
// Created by rodion on 8/2/20.
//

#include "TaskView.h"

void TaskView::addTask(const std::shared_ptr<TaskEntity> &task) {
  prioritySorted.insert(std::make_pair(task->getPriority(), task));
  nameSorted.insert(std::make_pair(task->getName(), task));
  labelSorted.insert(std::make_pair(task->getLabel(), task));
  dateSorted.insert(std::make_pair(task->getDueTime(), task));
}


std::vector<TaskEntity> TaskView::getAllTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [key, value] : prioritySorted) {
    searchResult.push_back(*value);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTodayTasks() {
  std::vector<TaskEntity> searchResult;
  auto now = getCurrentTime();
  for(auto [date, task] : dateSorted) {
    if (now.getYear() == date.getTime().getYear() && now.getMonth() == date.getTime().getMonth()
        && now.getDay() == date.getTime().getDay()) {
      searchResult.push_back(*task);
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getWeekTasks() {
  std::vector<TaskEntity> searchResult;
  auto leftBorder = getCurrentTime();
  auto rightBorder = addWeek(leftBorder);
  for(auto [date, task] : dateSorted) {
    if(date > leftBorder && date < rightBorder) searchResult.push_back(*task);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByPriority(const Task::Priority &priority) {
  auto first = prioritySorted.find(priority);
  std::vector<TaskEntity> searchResult;

  if(first == prioritySorted.end()) return searchResult;
  else {
    for(auto it = first; it != prioritySorted.end(); ++it) {
      if(it->first != priority) break;
      searchResult.push_back(*it->second);
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByName(const std::string &name) {
  auto first = nameSorted.find(name);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != nameSorted.end(); ++it) {
    if(it->first != name) break;
    searchResult.push_back(*it->second);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByLabel(const std::string &label) {
  auto first = labelSorted.find(label);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != labelSorted.end(); ++it) {
    if(it->first != label) break;
    searchResult.push_back(*it->second);
  }
  return searchResult;
}