//
// Created by Rodion Shyshkin on 26.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKSTATE_H_
#define TODOLIST_TESTS_MOCKS_MOCKSTATE_H_

#include <gmock/gmock.h>
#include <States/StateInterface.h>

class MockState : public StateInterface {
 public:
  MOCK_METHOD(StateResult, run, (std::shared_ptr<Context>), (override));
  MOCK_METHOD(std::unique_ptr<StateInterface>, switchState, (), (override));
  MOCK_METHOD(StateType, getType, (), (override));

 private:
  MOCK_METHOD(bool, input, (const std::shared_ptr<IOInterface>&), (override));
  MOCK_METHOD(void, output, (const std::shared_ptr<IOInterface>&), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKSTATE_H_
