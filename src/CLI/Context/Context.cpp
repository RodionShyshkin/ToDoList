//
// Created by rodion on 8/26/20.
//

#include "Context.h"

Context::Context() {
  this->service_ = std::make_unique<FakeService>();
}