//
// Created by rodion on 8/2/20.
//

#include "TaskView.h"

template <typename T>
bool findByID(const TaskID& id, std::multimap<T, std::pair<TaskID, std::weak_ptr<TaskEntity>>> map) {
  for(auto [first, second] : map) {
    if(second.first == id) return true;
  }
  return false;
}

template <typename T>
bool removeFromMap(const TaskID& id, std::multimap<T, std::pair<TaskID, std::weak_ptr<TaskEntity>>> map) {
  for(auto it = map.begin(); it != map.end(); ++it) {
    if(it->second.first == id) {
      map.erase(it);
      return true;
    }
  }
  return false;
}

template <typename T>
bool substituteInMap(const TaskID& id, const Task& newtask, std::multimap<T, std::pair<TaskID,
                     std::weak_ptr<TaskEntity>>> map) {
  for(auto it = map.begin(); it != map.end(); ++it) {
    if(it->second.first == id) {
      it->second.second.lock()->SubstituteTask(newtask);
      return true;
    }
  }
  return false;
}

bool TaskView::AddTask(const std::weak_ptr<TaskEntity> &task) {
  auto id = task.lock()->GetID();
  auto pairTask = std::make_pair(task.lock()->GetID(), task);

  if(findByID(id, priority_sorted_) || findByID(id, name_sorted_) ||
    findByID(id, label_sorted_) || findByID(id, date_sorted_)) return false;
  priority_sorted_.insert(std::make_pair(task.lock()->GetPriority(), pairTask));
  name_sorted_.insert(std::make_pair(task.lock()->GetName(), pairTask));
  label_sorted_.insert(std::make_pair(task.lock()->GetLabel(), pairTask));
  date_sorted_.insert(std::make_pair(task.lock()->GetDueTime(), pairTask));
  return true;
}

bool TaskView::RemoveTask(const TaskID& id) {
  if(!removeFromMap(id, priority_sorted_)) return false;
  if(!removeFromMap(id, name_sorted_)) return false;
  if(!removeFromMap(id, label_sorted_)) return false;
  if(!removeFromMap(id, date_sorted_)) return false;
  return true;
}

std::vector<TaskEntity> TaskView::GetAllTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [key, value] : priority_sorted_) {
    searchResult.push_back(*(value.second.lock()));
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTodayTasks() {
  std::vector<TaskEntity> searchResult;
  auto today = Date::GetCurrentDate();
  for(auto [date, task] : date_sorted_) {
    if(date.GetDate() == today.GetDate()) searchResult.push_back(*(task.second.lock()));
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetWeekTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [date, task] : date_sorted_) {
    if(Date::CheckWeek(date)) searchResult.push_back(*(task.second.lock()));
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(const Priority &priority) {
  auto first = priority_sorted_.find(priority);
  std::vector<TaskEntity> searchResult;

  if(first == priority_sorted_.end()) return searchResult;
  else {
    for(auto it = first; it != priority_sorted_.end(); ++it) {
      if(it->first != priority) break;
      searchResult.push_back(*it->second.second.lock());
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string &name) {
  auto first = name_sorted_.find(name);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != name_sorted_.end(); ++it) {
    if(it->first != name) break;
    searchResult.push_back(*it->second.second.lock());
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string &label) {
  auto first = label_sorted_.find(label);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != label_sorted_.end(); ++it) {
    if(it->first != label) break;
    searchResult.push_back(*it->second.second.lock());
  }
  return searchResult;
}