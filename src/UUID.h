//
// Created by rodion on 7/22/20.
//

#ifndef TODOLIST_SRC_UUID_H_
#define TODOLIST_SRC_UUID_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class UUID {
 public:
  UUID();
  ~UUID();

 public:
  friend std::ostream& operator<< (std::ostream &out, const UUID &taskid);

 private:
  boost::uuids::uuid id;
};

#endif //TODOLIST_SRC_UUID_H_
