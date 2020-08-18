//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_TASKENTITY_H_
#define TODOLIST_SRC_TASKENTITY_H_

#include "Task.h"
#include "MemoryModel/Storage/IDGenerator.h"
#include "TaskID.h"

/*
 * \brief Full task with ID, subtasks and status.
 *
 * @author Rodion Shyshkin
 */

class TaskEntity {
 public:
  TaskEntity();

 public:
  /*
   * Factory method for TaskEntity. Doesn't return an optional because
   * all its params are already validated.
   *
   * @param Task task with the main information
   * @param TaskID identifier for task.
   *
   * @return TaskEntity Task without any parent tasks (it isn't a subtask of some task).
   */
  static TaskEntity                                       createTask(const Task& task, const TaskID& id);

  /*
   * Factory method for TaskEntity. Doesn't return an optional because
   * all its params are already validated.
   *
   * @param Task task with the main information
   * @param TaskID identifier for task
   * @param TaskID identifier of parent task
   *
   * @return TaskEntity Task which is a subtask of some another task => has a parent task.
   */
  static TaskEntity                                       createSubtask(const Task& task, const TaskID& id,
                                                                        const TaskID& parent);

 public:
  TaskID                                                  GetID() const;
  std::string                                             GetName() const;
  std::string                                             GetLabel() const;
  Priority                                                GetPriority() const;
  Date                                                    GetDueTime() const;
  bool                                                    GetStatus() const;
  Task                                                    GetTask() const;
  std::map<TaskID, std::weak_ptr<TaskEntity>>             GetSubtasks() const;
  TaskID                                                  GetParentID() const;

 public:
  /*
   * Adds subtask for current task.
   *
   * @param const std::shared_ptr<TaskEntity>& reference to the TaskEntity smart pointer.
   */
  void                                                    AddSubtask(const std::weak_ptr<TaskEntity> &task);

  /*
   * Changes task status.
   *
   * @return bool True if task old status is false, False in another case.
   */
  bool                                                    SetComplete();

  /*
   * Changes Task date.
   *
   * @return bool True if new date is not less then old date, False in another case.
   */
  bool                                                    SubstituteTask(const Task &newtask);

  /*
   * Removes subtasks.
   *
   * @param taskID id of the subtask.
   *
   * @return True if the task has subtask with this id and it was removed, False in another case.
   */
  bool                                                    RemoveSubtask(const TaskID& id);

  /*
   * Checks if a task has parent.
   *
   * @return bool True if it has, False in another case.
   */
  bool                                                    checkParent();

 private:
  TaskEntity(const Task &task, const TaskID &id, const TaskID& parent);

 private:
  TaskID                                                  user_id_;
  bool                                                    status_;
  Task                                                    task_;
  std::map<TaskID, std::weak_ptr<TaskEntity>>             subtasks_;
  TaskID                                                  parent_id_;
};

#endif //TODOLIST_SRC_FULLTASK_H_
