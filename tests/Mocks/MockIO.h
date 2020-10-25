//
// Created by Rodion Shyshkin on 26.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKIO_H_
#define TODOLIST_TESTS_MOCKS_MOCKIO_H_

#include <gmock/gmock.h>
#include <IO/IOInterface.h>

class MockIO : public IOInterface {
 public:
  MOCK_METHOD(std::string, input, (), (override));
  MOCK_METHOD(std::string, inputCommand, (), (override));
  MOCK_METHOD(void, output, (const std::string&), (override));
  MOCK_METHOD(void, outputWithBreak, (const std::string&), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKIO_H_
