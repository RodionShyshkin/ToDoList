//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_ADDTASKBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_ADDTASKBUFFER_H_

#include <Context/BufferInterface.h>
#include <API/Priority.h>
#include <boost/date_time/gregorian/greg_date.hpp>

/*
 * Buffer with temporary data for adding task.
 *
 * @see BufferInterface.h
 *
 * @author: Rodion Shyshkin
 */

class AddTaskBuffer : public BufferInterface {
 public:
  AddTaskBuffer();

 public:
  void        clearBuffer()                                                 override;
  bool        checkBufferFullness()                                 const   override;

 public:
  void                    setName(const std::string&);
  void                    setLabel(const std::string&);
  void                    setPriority(const Priority&);
  void                    setDate(const boost::gregorian::date&);
  void                    setParent(const unsigned int&);

  std::string             getName()                                 const;
  std::string             getLabel()                                const;
  Priority                getPriority()                             const;
  boost::gregorian::date  getDate()                                 const;
  unsigned int            getParent()                               const;

 private:
  std::string             name_;
  std::string             label_;
  Priority                priority_;
  boost::gregorian::date  date_;
  unsigned int            parent_id_;
  bool                    is_subtask_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_ADDTASKBUFFER_H_
