//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_IDBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_IDBUFFER_H_

#include <Context/BufferInterface.h>
#include <optional>

class IDBuffer : public BufferInterface {
 public:
  IDBuffer();

 public:
  void clearBuffer() override;
  bool checkBufferFullness() const override;

 public:
  void setID(const unsigned int&);

  std::optional<unsigned int> getID() const;

 private:
  bool has_id_;
  unsigned int id_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_IDBUFFER_H_
