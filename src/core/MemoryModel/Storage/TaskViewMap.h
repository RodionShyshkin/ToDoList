//
// Created by Rodion Shyshkin on 27.10.2020.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_TASKVIEWMAP_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_TASKVIEWMAP_H_

#include <MemoryModel/Task/TaskID.h>
#include <map>
#include <MemoryModel/Task/TaskEntity.h>

namespace task_view_map {
  template <typename T>
  bool FindByID(const TaskID& id, std::map<T, std::map<TaskID, std::weak_ptr<TaskEntity>>> map) {
    for(const auto& [type, tasks] : map) {
      for(const auto& [ID, task] : tasks) {
        if (ID == id) return true;
      }
    }
    return false;
  }

  template <typename T>
  bool RemoveFromMap(const TaskID& id, std::map<T, std::map<TaskID, std::weak_ptr<TaskEntity>>>& map) {
    for(auto& [type, tasks] : map) {
      for(const auto& [ID, task] : tasks) {
        if(ID == id) {
        tasks.erase(ID);
        return true;
      }
    }
  }
  return false;
  }
}

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_STORAGE_TASKVIEWMAP_H_
