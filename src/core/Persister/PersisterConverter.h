//
// Created by rodion on 10/20/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_

#include <task.pb.h>
#include <API/Utils/ProtoConverter.h>
#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

/*
 * \brief Toolkit for converting proto tasks to memory model structures and vice versa.
 *
 * @author Rodion Shyshkin
 */

namespace persister_converter {
  static void StorageToProto(const std::vector<ModelTaskDTO>& tasks, StorageProto& storage) {
    for(const auto& task : tasks) {
      auto* newTask = storage.add_tasks();
      TaskProto temporary;
      temporary = proto_converter::ModelDTOToProto(task);
      *newTask = temporary;
    }
  }
  static bool ProtoToModel(const StorageProto& storage_proto, TaskModelInterface& model) {
    for(const auto& task : storage_proto.tasks()) {
      auto model_dto = proto_converter::TaskProtoToModelDTO(task);
      if(model_dto.GetParentID() == model_dto.GetID()) {
        auto result = model.AddTask(model_dto);
        if(result.GetError().has_value()) return false;
      }
      else {
        auto result = model.AddSubtask(model_dto.GetParentID(), model_dto);
        if(result.GetError().has_value()) return false;
      }
    }
    return true;
  }
}

#endif //TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
