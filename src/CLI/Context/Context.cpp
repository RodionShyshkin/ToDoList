//
// Created by rodion on 8/26/20.
//

#include "Context.h"

Context::Context(const std::shared_ptr<TaskServiceInterface> &service,
                 const std::shared_ptr<IOInterface> &io) {
  service_ = service;
  io_ = io;
}

void Context::clearAllBuffers() {
  id_buffer_.clearBuffer();
  show_list_buffer_.clearBuffer();
  postpone_buffer_.clearBuffer();
  add_task_buffer_.clearBuffer();
  filepath_buffer_.clearBuffer();
}