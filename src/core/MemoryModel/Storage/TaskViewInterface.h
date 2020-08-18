//
// Created by rodion on 8/17/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKVIEWINTERFACE_H_
#define TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKVIEWINTERFACE_H_

class TaskViewInterface {
 public:
  virtual ~TaskViewInterface() = default;

 public:
  virtual bool                                        AddTask(const std::weak_ptr<TaskEntity>& task) = 0;
  virtual bool                                        RemoveTask(const TaskID& id) = 0;

 public:
  virtual std::vector<TaskEntity>                     GetTodayTasks() = 0;
  virtual std::vector<TaskEntity>                     GetWeekTasks() = 0;

  virtual std::vector<TaskEntity>                     GetAllTasks() = 0;
  virtual std::vector<TaskEntity>                     GetTasksByLabel(const std::string& label) = 0;
  virtual std::vector<TaskEntity>                     GetTasksByName(const std::string& name) = 0;
  virtual std::vector<TaskEntity>                     GetTasksByPriority(const Priority& priority) = 0;
};

#endif //TODOLIST_SRC_MEMORYMODEL_STORAGE_TASKVIEWINTERFACE_H_
