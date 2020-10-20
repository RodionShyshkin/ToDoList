//
// Created by rodion on 10/20/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_

#include <task.pb.h>
#include <src/core/MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <src/core/MemoryModel/ModelAPI/TaskModelInterface.h>

class ProtoConverter {
 public:
  static void                 StorageToProto(const std::vector<ModelTaskDTO>&, StorageProto&);
  static bool                 ProtoToModel(const StorageProto&, TaskModelInterface&);

 private:
  static TaskProto            TaskToProto(const ModelTaskDTO&);
  static ModelTaskDTO         ProtoToTask(const TaskProto&);

 private:
  static TaskProto_Priority   PriorityToProto(const Priority&);
  static Priority             ProtoToPriority(const TaskProto_Priority&);
};

#endif //TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
