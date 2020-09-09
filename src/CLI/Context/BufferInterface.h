//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_
#define TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_

class BufferInterface {
 public:
  ~BufferInterface() = default;

 public:
  virtual void        clearBuffer() = 0;
  virtual bool        checkBufferFullness() const = 0;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_
