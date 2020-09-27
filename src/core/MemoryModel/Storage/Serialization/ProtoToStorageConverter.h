//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include <vector>
#include <task.pb.h>
#include <src/core/MemoryModel/Storage/FullStorage.h>

class ProtoToStorageConverter {
 public:
  static std::unique_ptr<FullStorage>      ConvertFromProto(const StorageProto&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_PROTOTOSTORAGECONVERTER_H_
