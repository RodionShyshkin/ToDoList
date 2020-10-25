//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_

#include <Context/BufferInterface.h>
#include <boost/date_time/gregorian/greg_date.hpp>

/*
 * Buffer for temporary information about the process of a task postponing.
 *
 * @see BufferInterface.h
 *
 * @author Rodion Shyshkin
 */

class PostponeBuffer : public BufferInterface {
 public:
  PostponeBuffer();

 public:
  void                    clearBuffer()                                     override;
  bool                    checkBufferFullness()                       const override;

 public:
  void                    setNewDate(const boost::gregorian::date&);

  boost::gregorian::date  getNewDate()                                const;

 private:
  boost::gregorian::date  new_date_;
  
};

#endif //TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_
