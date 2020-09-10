//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_

#include <Context/BufferInterface.h>
#include <States/GetTasksList/ListModifier.h>

class ShowListBuffer : public BufferInterface {
 public:
  ShowListBuffer();

 public:
  void clearBuffer() override;
  bool checkBufferFullness() const override;

 public:
  void setModifier(const ListModifier&);
  void setSortedFlag(const bool&);

 public:
  ListModifier getModifier() const;
  bool getSortedFlag() const;

 private:
  ListModifier modifier_;
  bool is_sorted_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_
