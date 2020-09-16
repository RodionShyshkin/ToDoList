//
// Created by rodion on 8/26/20.
//

#include "Context.h"

Context::Context() {
  this->service_ = std::make_unique<FakeService>();
}

void Context::clearAllBuffers() {
  this->id_buffer_.clearBuffer();
  this->show_list_buffer_.clearBuffer();
  this->postpone_buffer_.clearBuffer();
  this->add_task_buffer_.clearBuffer();
}