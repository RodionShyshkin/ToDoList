//
// Created by rodion on 8/26/20.
//

#include "Context.h"

Context::Context(const std::shared_ptr<TaskServiceInterface> &service,
                 const std::shared_ptr<IOInterface> &io) {
  this->service_ = service;
  this->io_ = io;
}

void Context::clearAllBuffers() {
  this->id_buffer_.clearBuffer();
  this->show_list_buffer_.clearBuffer();
  this->postpone_buffer_.clearBuffer();
  this->add_task_buffer_.clearBuffer();
}