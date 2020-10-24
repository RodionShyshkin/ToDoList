//
// Created by Rodion Shyshkin on 24.10.2020.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_FILEPATHBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_FILEPATHBUFFER_H_

#include <string>
#include "BufferInterface.h"

class FilepathBuffer : public BufferInterface {
 public:
  FilepathBuffer();

 public:
  void clearBuffer() override;
  bool checkBufferFullness() const override;

 public:
  void setFilepath(const std::string& path);

  std::string getFilepath() const;

 private:
  std::string filepath_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_FILEPATHBUFFER_H_
