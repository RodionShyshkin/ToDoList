//
// Created by rodion on 10/19/20.
//
/*
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachine.h>

using ::testing::Return;

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(TaskDTO, GetTask, (const unsigned int&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult<StorageError>, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, add_subtask_graph, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(bool, postpone_task_graph, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(bool, CompleteTask, (const unsigned int&), (override));

  MOCK_METHOD(OperationResult<PersistError>, Save, (const std::string&), (override));
  MOCK_METHOD(OperationResult<PersistError>, Load, (const std::string&), (override));
};

class MockIO : public IOInterface {
 public:
  MOCK_METHOD(std::string, input, (), (override));
  MOCK_METHOD(std::string, inputCommand, (), (override));
  MOCK_METHOD(void, output, (const std::string&), (override));
  MOCK_METHOD(void, outputWithBreak, (const std::string&), (override));
};

class SaveLoadCommandsTest : public ::testing::Test {
 public:
  void SetUp() override {
    this->service_ = std::make_shared<MockService>();
    this->io_ = std::make_shared<MockIO>();
    this->context_ = std::make_shared<Context>(this->service_, this->io_);
  }

  void TearDown() override {

  }

 protected:
  std::shared_ptr<MockService> service_;
  std::shared_ptr<MockIO> io_;
  std::shared_ptr<Context> context_;
};

TEST_F(SaveLoadCommandsTest, shouldSaveCorrectly) {
  EXPECT_CALL(*io_, inputCommand).Times(4).WillOnce(Return("add"))
                                              .WillOnce(Return("mm"))
                                              .WillOnce(Return("save"))
                                              .WillOnce(Return("exit"));
  EXPECT_CALL(*io_, input).Times(5).WillOnce(Return("name"))
                                        .WillOnce(Return("label"))
                                        .WillOnce(Return(""))
                                        .WillOnce(Return(""))
                                        .WillOnce(Return("clitest.txt"));
  EXPECT_CALL(*service_, add_task_graph).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*service_, Save).Times(1).WillOnce(Return(OperationResult<PersistError>::Success()));

  EXPECT_CALL(*io_, outputWithBreak).Times(17);
  EXPECT_CALL(*io_, output).Times(5);

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::MAIN, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
}

TEST_F(SaveLoadCommandsTest, shouldLoadCorrectly) {
  EXPECT_CALL(*io_, inputCommand).Times(2).WillOnce(Return("load"))
      .WillOnce(Return("exit"));
  EXPECT_CALL(*io_, input).Times(1).WillOnce(Return("clitest.txt"));
  EXPECT_CALL(*service_, Load).Times(1).WillOnce(Return(OperationResult<PersistError>::Success()));

  EXPECT_CALL(*io_, outputWithBreak).Times(8);
  EXPECT_CALL(*io_, output).Times(1);

  StateMachine task_machine_ = StateMachine::Create(StatesMachineType::MAIN, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
}
*/