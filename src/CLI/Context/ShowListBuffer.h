//
// Created by rodion on 9/9/20.
//

#ifndef TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_
#define TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_

#include <Context/BufferInterface.h>
#include <States/ListModifier.h>
#include <API/TaskDTO.h>

/*
 * Buffer for keeping data about process of getting list of tasks.
 *
 * @see BufferInterface.h
 *
 * @author Rodion Shyshkin
 */

class ShowListBuffer : public BufferInterface {
 public:
  ShowListBuffer();

 public:
  void                  clearBuffer()                 override;
  bool                  checkBufferFullness()   const override;

 public:
  void                  setModifier(const ListModifier&);
  void                  setSortedFlag(const bool&);
  void                  setLabel(const std::string&);
  void                  setList(const std::vector<TaskDTO>&);

  ListModifier          getModifier()           const;
  bool                  getSortedFlag()         const;
  std::string           getLabel()              const;
  bool                  getByLabelFlag()        const;
  std::vector<TaskDTO>  getList()               const;

 private:
  ListModifier          modifier_;
  bool                  is_sorted_;
  std::string           label_;
  std::vector<TaskDTO>  list_;
  bool                  is_by_label_;
};

#endif //TODOLIST_SRC_CLI_CONTEXT_SHOWLISTBUFFER_H_
