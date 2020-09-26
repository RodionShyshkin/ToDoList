//
// Created by rodion on 9/25/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include "task.pb.h"

class TaskSerializer {
 public:
  static TaskProto    SerializeTaskWithSubtasks(const TaskEntity&);

 private:
  static TaskProto*   SerializeTask(const TaskEntity&);
  static TaskProto_Priority     SerializePriority(const Priority&);
  static void         SetTaskProtoFields(TaskProto* task, const TaskEntity& task_entity);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKSERIALIZER_H_
