//
// Created by rodion on 9/25/20.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_

#include <src/core/MemoryModel/Task/TaskEntity.h>
#include <src/core/MemoryModel/Storage/ModelTaskDTO.h>
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
  static TaskProto    ConvertTaskEntityToProto(const ModelTaskDTO&);

 private:
  /*
   * Converts TaskEntity instance without subtasks.
   *
   * @param TaskEntity instance.
   *
   * @return TaskProto* pointer.
   */
  static std::unique_ptr<TaskProto>  ConvertSingleTask(const ModelTaskDTO&);

  /*
   * Converts Priority to TaskProto_Priority.
   *
   * @param Priority instance.
   *
   * @return the TaskProto_Priority one.
   */
  static TaskProto_Priority     ConvertPriority(const Priority&);

  /*
   * Copies fields about task from TaskEntity instance to the TaskProto one.
   *
   * @param TaskProto* a pointer to a TaskProto instance to update its fields.
   * @param TaskEntity by a reference in which there is new data.
   */
  static void         SetTaskProtoFields(TaskProto* task, const ModelTaskDTO& task_entity);
};

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_SERIALIZATION_TASKTOPROTOCONVERTER_H_
