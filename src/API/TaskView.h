//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKVIEW_H_
#define TODOLIST_SRC_API_TASKVIEW_H_

#include <map>
#include <TaskEntity.h>
class TaskView {
 public:
  void addTask(const std::shared_ptr<TaskEntity>& task);

 public:
  std::vector<TaskEntity>         getAllTasks();
  std::vector<TaskEntity>         getTodayTasks();
  std::vector<TaskEntity>         getWeekTasks();
  std::vector<TaskEntity>         getTasksByLabel(const std::string& label);
  std::vector<TaskEntity>         getTasksByName(const std::string& name);
  std::vector<TaskEntity>         getTasksByPriority(const Task::Priority& priority);

 private:
  std::multimap<Task::Priority, std::shared_ptr<TaskEntity>>    priority_sorted;
  std::multimap<std::string, std::shared_ptr<TaskEntity>>       name_sorted;
  std::multimap<std::string, std::shared_ptr<TaskEntity>>       label_sorted;
  std::multimap<DueTime, std::shared_ptr<TaskEntity>>           date_sorted;
};

#endif //TODOLIST_SRC_API_TASKVIEW_H_
