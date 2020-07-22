//
// Created by rodion on 7/22/20.
//

#include "UUID.h"

UUID::UUID() {
  this->id = boost::uuids::random_generator()();
}

UUID::~UUID() = default;

std::ostream& operator<< (std::ostream &out, const UUID &uuid) {
  out << uuid.id;
  return out;
}
