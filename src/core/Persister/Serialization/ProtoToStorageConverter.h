//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include <vector>
#include <task.pb.h>
#include <src/core/MemoryModel/ModelAPI/TaskModel.h>

/*
 * This converter gets task model from a StorageProto instance.
 *
 * @see task.proto
 *
 * @author Rodion Shyshkin
 */

class ProtoToStorageConverter {
 public:
  static void   ConvertProtoToStorage(const StorageProto&, TaskModelInterface&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_
