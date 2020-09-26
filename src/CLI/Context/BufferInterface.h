//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_
#define TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_

/*
 * Interface which describes common properties for buffers Context contains.
 *
 * @see Context.h
 *
 * @author: Rodion Shyshkin
 */

class BufferInterface {
 public:
  ~BufferInterface() = default;

 public:
  /*
   * Clears buffer.
   */
  virtual void        clearBuffer() = 0;

  /*
   * Check if buffer was filled.
   *
   * @return True if buffer is filled, False in another case.
   */
  virtual bool        checkBufferFullness() const = 0;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_BUFFERINTERFACE_H_
