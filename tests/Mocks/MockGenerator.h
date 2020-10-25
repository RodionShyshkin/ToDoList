//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKGENERATOR_H_
#define TODOLIST_TESTS_MOCKS_MOCKGENERATOR_H_

#include <MemoryModel/Storage/IDGeneratorInterface.h>
#include <gmock/gmock.h>

class MockGenerator : public IDGeneratorInterface {
 public:
  MOCK_METHOD(TaskID, GenerateID, (), (override));
};
#endif //TODOLIST_TESTS_MOCKS_MOCKGENERATOR_H_
