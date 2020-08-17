//
// Created by rodion on 7/18/20.
//

#ifndef TODOLIST_SRC_TASKID_H_
#define TODOLIST_SRC_TASKID_H_

#include <optional>

/*
 * \brief A class for {Task} identifying which guarantees its uniqueness.
 *
 * @author Rodion Shyshkin
 */

class TaskID {
 public:
  TaskID();

 public:
  static std::optional<TaskID>    create(const unsigned int& id);

 public:
  unsigned int                    GetID() const;

 private:
  unsigned int                    id_;

 private:
  TaskID(const unsigned int& id);
};

bool operator== (const TaskID& lhs, const TaskID& rhs);
bool operator< (const TaskID& lhs, const TaskID& rhs);

#endif //TODOLIST_SRC_TASKID_H_
