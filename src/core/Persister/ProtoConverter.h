//
// Created by rodion on 10/20/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_

#include <task.pb.h>
#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

/*
 * \brief Toolkit for converting proto tasks to memory model structures and vice versa.
 *
 * @author Rodion Shyshkin
 */

namespace proto_converter {

  static proto::Priority PriorityToProto(const Priority& priority) {
    if(Priority::EMPTY == priority) return proto::Priority::EMPTY;
    else if(Priority::LOW == priority) return proto::Priority::LOW;
    else if(Priority::MEDIUM == priority) return proto::Priority::MEDIUM;
    else if(Priority::HIGH == priority) return proto::Priority::HIGH;
    throw std::runtime_error("Invalid priority convertion.");
  }

  static Priority ProtoToPriority(const proto::Priority& priority) {
    if(proto::Priority::EMPTY == priority) return Priority::EMPTY;
    else if(proto::Priority::LOW == priority) return Priority::LOW;
    else if(proto::Priority::MEDIUM == priority) return Priority::MEDIUM;
    else if(proto::Priority::HIGH == priority) return Priority::HIGH;
    throw std::runtime_error("Invalid priority convertion.");
  }


  static proto::TaskProto TaskToProto(const ModelTaskDTO& task) {
    auto newtask = std::make_unique<proto::TaskProto>();
    newtask->set_name(task.GetName());
    newtask->set_label(task.GetLabel());
    newtask->set_priority(PriorityToProto(task.GetPriority()));
    newtask->set_deadline(task.GetDueDate().GetDate().day_number());
    newtask->set_completed(task.GetStatus());

    auto parent = task.GetParentID();
    if(parent == task.GetID()) newtask->set_parent_id(0);
    else newtask->set_parent_id(parent.GetID());
    return *newtask;
  }

  static ModelTaskDTO ProtoToTask(const proto::TaskProto& task) {
    return ModelTaskDTO::CreateWithParent(TaskID{0}, task.name(), task.label(),
                                          proto_converter::ProtoToPriority(task.priority()),
                                          Date{boost::gregorian::date{task.deadline()}}, task.completed(),
                                          TaskID{task.parent_id()});
  }

  static void StorageToProto(const std::vector<ModelTaskDTO>& tasks, proto::StorageProto& storage) {
    for(const auto& task : tasks) {
      auto* newTask = storage.add_tasks();
      proto::TaskProto temporary;
      temporary = proto_converter::TaskToProto(task);
      *newTask = temporary;
    }
  }
  static bool ProtoToModel(const proto::StorageProto& storage_proto, TaskModelInterface& model) {
    for(const auto& task : storage_proto.tasks()) {
      auto model_dto = proto_converter::ProtoToTask(task);
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
