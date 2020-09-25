//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <API/TaskDTO.h>
#include <MemoryModel/Storage/FullStorageInterface.h>

class FullStorage : public FullStorageInterface {
 public:
  FullStorage();

 public:
  TaskView                          GetTaskView() const override;
  TaskStorage                       GetTaskStorage() const override;

  OperationResult                   AddTask(const TaskDTO& task) override;
  OperationResult                   AddSubtask(const TaskID &id, const TaskDTO& subtask) override;
  OperationResult                   RemoveTask(const TaskID& id) override;

  OperationResult                   SaveToDisk(const std::string&) override;
  OperationResult                   LoadFromDisk(const std::string&) override;

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  IDGenerator                       generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
