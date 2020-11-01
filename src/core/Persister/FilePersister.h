//
// Created by rodion on 9/27/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_

#include <Persister/PersisterInterface.h>
#include <Persister/PersisterConverter.h>
#include <fstream>

/*
 * \brief Persister, inherited from PersisterInterface, which saves/loads ToDoList from a file.
 *
 * @see TaskService.h
 *
 * @author Rodion Shyshkin
 */

class FilePersister : public PersisterInterface {
 public:
  FilePersister(std::fstream&& file, TaskModelInterface& model);

 public:
  bool                  Save() override;
  bool                  Load() override;

 private:
  std::fstream          file_;
  TaskModelInterface&   model_;
};

#endif //TODOLIST_SRC_CORE_PERSISTER_FILEPERSISTER_H_
