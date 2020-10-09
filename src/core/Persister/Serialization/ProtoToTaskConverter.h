//
// Created by rodion on 9/26/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_

#include <src/core/MemoryModel/CoreAPI/ModelTaskDTO.h>
#include "task.pb.h"

/*
 * Class contains static methods to convert TaskProto to ModelTaskDTO.
 *
 * @see task.proto
 *
 * @author Rodion Shyshkin
 */

class ProtoToTaskConverter {
 public:
  /*
   * Converts TaskProto to ModelTaskDTO.
   *
   * @param TaskProto
   *
   * @return ModelTaskDTO
   */
  static ModelTaskDTO       ConvertProtoToTask(const TaskProto&);

 private:
  /*
   * \brief Converts TaskProto_Priority to Priority.
   *
   * @param TaskProto_Priority instance.
   *
   * @return Priority instance.
   */
  static Priority         ConvertProtoToPriority(const TaskProto_Priority&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTO_TASKDESERIALIZER_H_
