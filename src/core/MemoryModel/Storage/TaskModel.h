//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
#define TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_

#include <MemoryModel/Storage/TaskModelInterface.h>

class TaskModel : public TaskModelInterface {
 public:
  TaskModel();

 public:
  TaskView                          GetTaskView() const override;
  TaskStorage                       GetTaskStorage() const override;

  OperationResult                   AddTask(const ModelTaskDTO& task) override;
  OperationResult                   AddSubtask(const TaskID &id, const ModelTaskDTO& subtask) override;
  OperationResult                   RemoveTask(const TaskID& id) override;

  /*
   * \brief Method which saves storage to a disk.
   *
   * @param std::string path to file in which storage would be saved.
   *
   * @return OperationResult The result of saving.
   * Should return NO_ERRORS in the case of success,
   * UNKNOWN_PATH if there is a problem with opening file,
   * SERIALIZATION_ERROR if serialization returns false.
   */
  OperationResult                   SaveToDisk(const std::string&) const override;

  /*
   * \brief Method which loads storage from a disk.
   *
   * @param std::string path to file with storage.
   *
   * @return OperationREsult The result of saving.
   * Should return NO_ERRORS in the case of success.
   * UNKNOWN_PATH if there are no such a file.
   * DESERIALIZATION_ERROR if deserialization returns false.
   * INVALID_TASK if some serialized tasks are invalid.
   */
  OperationResult                   LoadFromDisk(const std::string&) const override;

 private:
  TaskStorage                       task_storage_;
  TaskView                          task_view_;
  IDGenerator                       generate_id_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_FULLSTORAGE_H_
