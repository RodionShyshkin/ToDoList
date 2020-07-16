//
// Created by rodion on 7/16/20.
//

#ifndef TODOLIST__TASKID_H_
#define TODOLIST__TASKID_H_

class TaskID {
 public:
    static unsigned int generateID() {
      return ++ids;
    }

 private:
  static unsigned int ids;
};

#endif //TODOLIST__TASKID_H_
