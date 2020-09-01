//
// Created by rodion on 8/28/20.
//

#include "ShowListContext.h"

ShowListContext::ShowListContext() {
  updateContext(ListModifier::UNKNOWN, false);
}

void ShowListContext::updateContext(const ListModifier &modifier, const bool &is_sorted) {
  this->modifier_ = modifier;
  this->is_sorted_ = is_sorted;
}

ListModifier ShowListContext::getModifier() const {
  return modifier_;
}

bool ShowListContext::getSorted() const {
  return is_sorted_;
}