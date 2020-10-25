//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKSTORAGE_H_
#define TODOLIST_TESTS_MOCKS_MOCKSTORAGE_H_

#include <gmock/gmock.h>
#include <MemoryModel/Storage/TaskStorageInterface.h>

class MockStorage : public TaskStorageInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::shared_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));
  MOCK_METHOD(std::shared_ptr<TaskEntity>, GetTask, (const TaskID&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetAllTasks, (), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKSTORAGE_H_
