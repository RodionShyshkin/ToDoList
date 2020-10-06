//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_STORAGETOPROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_STORAGETOPROTOCONVERTER_H_

#include <task.pb.h>
#include <src/core/MemoryModel/Task/TaskEntity.h>
#include <src/core/Persister/Serialization/TaskToProtoConverter.h>
#include <src/core/MemoryModel/CoreAPI/TaskModel.h>

class StorageToProtoConverter {
 public:
  static StorageProto       ConvertStorageToProto(const std::vector<ModelTaskDTO>&);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_STORAGETOPROTOCONVERTER_H_
