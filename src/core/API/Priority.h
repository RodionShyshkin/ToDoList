//
// Created by rodion on 8/11/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_PRIORITY_H_
#define TODOLIST_SRC_MEMORYMODEL_PRIORITY_H_

enum class Priority {
  EMPTY,
  LOW,
  MEDIUM,
  HIGH
};

std::string stringByPriority(const Priority& priority);

#endif //TODOLIST_SRC_MEMORYMODEL_PRIORITY_H_
