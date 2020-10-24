//
// Created by Rodion Shyshkin on 24.10.2020.
//

#include "FilepathBuffer.h"

FilepathBuffer::FilepathBuffer() {
  clearBuffer();
}

bool FilepathBuffer::checkBufferFullness() const {
  return !filepath_.empty();
}

void FilepathBuffer::clearBuffer() {
  filepath_ = "";
}

std::string FilepathBuffer::getFilepath() const {
  return filepath_;
}

void FilepathBuffer::setFilepath(const std::string &path) {
  filepath_ = path;
}