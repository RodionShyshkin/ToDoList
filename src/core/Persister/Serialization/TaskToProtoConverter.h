//
// Created by rodion on 9/25/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include <src/core/MemoryModel/CoreAPI/ModelTaskDTO.h>
#include "task.pb.h"

/*
 * Class which contains static methods to convert TaskEntity into TaskProto.
 *
 * @see task.proto
 *
 * @author Rodion Shyshkin
 */

class TaskToProtoConverter {
 public:
  static TaskProto    ConvertTaskToProto(const ModelTaskDTO&);

 private:
  /*
   * Converts Priority to TaskProto_Priority.
   *
   * @param Priority instance.
   *
   * @return the TaskProto_Priority one.
   */
  static TaskProto_Priority     ConvertPriorityToProto(const Priority&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_
