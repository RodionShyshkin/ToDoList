//
// Created by rodion on 8/26/20.
//

#include "StateFactory.h"

std::unique_ptr<StateInterface> StateFactory::create(const StateType &type) {
  auto states_map = StatesMap::create();
  if(states_map.find(type) == states_map.end()) return nullptr;
  return std::move(states_map[type]);
}