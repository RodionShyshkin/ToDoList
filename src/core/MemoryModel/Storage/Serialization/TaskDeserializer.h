//
// Created by rodion on 9/26/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include "task.pb.h"

/*
 * Class contains static methods to convert TaskProto to TaskEntity.
 *
 * @see task.proto
 *
 * @author Rodion Shyshkin
 */

class TaskDeserializer {
 public:
  static std::shared_ptr<TaskEntity>       DeserializeTask(const TaskProto&);

 private:
  /*
   * \brief Converts TaskProto_Priority to Priority.
   *
   * @param TaskProrot_Priority
   *
   * @return Priority instance.
   */
  static Priority         DeserializePriority(const TaskProto_Priority&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_
