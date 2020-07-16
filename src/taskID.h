//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST_SRC_TASKID_H_
#define TODOLIST_SRC_TASKID_H_

class taskID {
 public:
  static unsigned int generateID() {
    return ++ids;
  }

 private:
  static unsigned int ids;
};

#endif //TODOLIST_SRC_TASKID_H_
