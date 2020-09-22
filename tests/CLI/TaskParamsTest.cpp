//
// Created by rodion on 9/22/20.
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

 class TaskParamsTest : public ::testing::Test {
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

TEST_F(TaskParamsTest, shouldAddTaskWithFilledFields) {
  EXPECT_CALL(*io_, input).Times(4).WillOnce(Return("name"))
                                        .WillOnce(Return("label"))
                                        .WillOnce(Return("High"))
                                        .WillOnce(Return("2012-9-14"));
  EXPECT_CALL(*io_, output).Times(4);

  StateMachine task_machine_ = StateMachine::create(StatesGraphType::ADDTASK, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->add_task_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->add_task_buffer_.getName(), "name");
  ASSERT_EQ(context_->add_task_buffer_.getLabel(), "label");
  ASSERT_EQ(context_->add_task_buffer_.getPriority(), Priority::HIGH);
  ASSERT_EQ(context_->add_task_buffer_.getDate(), boost::gregorian::from_string("2012-9-14"));
  ASSERT_EQ(context_->add_task_buffer_.getParent(), 0);
}

TEST_F(TaskParamsTest, shouldAddTaskWithUnfilledFields) {
  EXPECT_CALL(*io_, input).Times(4).WillOnce(Return("name"))
                                  .WillOnce(Return(""))
                                  .WillOnce(Return(""))
                                  .WillOnce(Return(""));
  EXPECT_CALL(*io_, output).Times(4);

  StateMachine task_machine_ = StateMachine::create(StatesGraphType::ADDTASK, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->add_task_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->add_task_buffer_.getName(), "name");
  ASSERT_EQ(context_->add_task_buffer_.getLabel(), "");
  ASSERT_EQ(context_->add_task_buffer_.getPriority(), Priority::EMPTY);
  ASSERT_EQ(context_->add_task_buffer_.getDate(), boost::gregorian::date{boost::gregorian::not_a_date_time});
  ASSERT_EQ(context_->add_task_buffer_.getParent(), 0);
}

TEST_F(TaskParamsTest, shouldNotAddTaskWithoutName) {
  EXPECT_CALL(*io_, input).Times(5).WillOnce(Return(""))
      .WillOnce(Return("name"))
      .WillOnce(Return(""))
      .WillOnce(Return(""))
      .WillOnce(Return(""));
  EXPECT_CALL(*io_, output).Times(5);
  EXPECT_CALL(*io_, outputWithBreak).Times(1);

  StateMachine task_machine_ = StateMachine::create(StatesGraphType::ADDTASK, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->add_task_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->add_task_buffer_.getName(), "name");
  ASSERT_EQ(context_->add_task_buffer_.getLabel(), "");
  ASSERT_EQ(context_->add_task_buffer_.getPriority(), Priority::EMPTY);
  ASSERT_EQ(context_->add_task_buffer_.getDate(), boost::gregorian::date{boost::gregorian::not_a_date_time});
  ASSERT_EQ(context_->add_task_buffer_.getParent(), 0);
}
