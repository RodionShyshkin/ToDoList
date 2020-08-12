//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKVIEW_H_
#define TODOLIST_SRC_API_TASKVIEW_H_

#include <map>
#include <MemoryModel/TaskEntity.h>

class TaskView {
 public:
  void                                                        AddTask(const std::shared_ptr<TaskEntity>& task);

 public:
  std::vector<TaskEntity>                                     GetTodayTasks();
  std::vector<TaskEntity>                                     GetWeekTasks();

  std::vector<TaskEntity>                                     GetAllTasks();
  std::vector<TaskEntity>                                     GetTasksByLabel(const std::string& label);
  std::vector<TaskEntity>                                     GetTasksByName(const std::string& name);
  std::vector<TaskEntity>                                     GetTasksByPriority(const Priority& priority);

 private:
  std::multimap<Priority, std::weak_ptr<TaskEntity>>          priority_sorted_;
  std::multimap<std::string, std::weak_ptr<TaskEntity>>       name_sorted_;
  std::multimap<std::string, std::weak_ptr<TaskEntity>>       label_sorted_;
  std::multimap<Date, std::weak_ptr<TaskEntity>>              date_sorted_;
};

#endif //TODOLIST_SRC_API_TASKVIEW_H_
