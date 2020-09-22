//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_

#include <Context/BufferInterface.h>
#include <boost/date_time/gregorian/greg_date.hpp>

class PostponeBuffer : public BufferInterface {
 public:
  PostponeBuffer();

 public:
  void                    clearBuffer()                                     override;
  bool                    checkBufferFullness()                       const override;

 public:
  void                    setNewDate(const boost::gregorian::date&);

  bool                    getSingleTaskFlag()                         const;
  boost::gregorian::date  getNewDate()                                const;

 private:
  boost::gregorian::date  new_date_;
  bool                    is_single_task_;
  
};

#endif //TODOLIST_SRC_CLI_CONTEXT_POSTPONEBUFFER_H_
