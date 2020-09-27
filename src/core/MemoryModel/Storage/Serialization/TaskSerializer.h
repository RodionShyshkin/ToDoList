//
// Created by rodion on 9/25/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include "task.pb.h"

/*
 * Class which contains static methods to convert TaskEntity into TaskProto.
 *
 * @see task.proto
 *
 * @author Rodion Shyshkin
 */

class TaskSerializer {
 public:
  static TaskProto    SerializeTaskWithSubtasks(const TaskEntity&);

 private:
  /*
   * Converts TaskEntity instance without subtasks.
   *
   * @param TaskEntity instance.
   *
   * @return TaskProto* pointer.
   */
  static std::unique_ptr<TaskProto>   SerializeTask(const TaskEntity&);

  /*
   * Converts Priority to TaskProto_Priority.
   *
   * @param Priority instance.
   *
   * @return the TaskProto_Priority one.
   */
  static TaskProto_Priority     SerializePriority(const Priority&);

  /*
   * Copies fields about task from TaskEntity instance to the TaskProto one.
   *
   * @param TaskProto* a pointer to a TaskProto instance to update its fields.
   * @param TaskEntity by a reference in which there is new data.
   */
  static void         SetTaskProtoFields(TaskProto* task, const TaskEntity& task_entity);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_
