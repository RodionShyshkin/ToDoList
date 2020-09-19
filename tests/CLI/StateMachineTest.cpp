//
// Created by rodion on 9/19/20.
//

#include <StateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(TaskDTO, getTask, (const TaskID&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, addSubtask, (const TaskID&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, RemoveTask, (const TaskID&), (override));
  MOCK_METHOD(OperationResult, postponeTask, (const TaskID&, const Date&), (override));
  MOCK_METHOD(OperationResult, completeTask, (const TaskID&), (override));
};

class MockIO : public IOInterface {
 public:
  MOCK_METHOD(std::string, input, (), (override));
  MOCK_METHOD(std::string, inputCommand, (), (override));
  MOCK_METHOD(void, output, (const std::string&), (override));
  MOCK_METHOD(void, outputWithBreak, (const std::string&), (override));
};

 class StateMachineTest : public ::testing::Test {
  public:

   void SetUp() override {
     this->io_ = std::make_shared<MockIO>();
     this->service_ = std::make_shared<MockService>();
   }

   void TearDown() override {

   }

  protected:
   std::shared_ptr<MockIO> io_;
   std::shared_ptr<MockService> service_;
};

TEST_F(StateMachineTest, gsad) {
//  EXPECT_CALL(*io_, inputCommand).Times(1).WillOnce(Return("add"));
  EXPECT_CALL(*service_, getAllTasks(true)).Times(1).WillOnce(Return(std::vector<TaskDTO>()));

}