//
// Created by rodion on 9/22/20.
//

#include <StateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(TaskDTO, getTask, (const unsigned int&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, addSubtask, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(OperationResult, postponeTask, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(OperationResult, completeTask, (const unsigned int&), (override));
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

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::ADDTASK, this->context_);
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

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::ADDTASK, this->context_);
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

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::ADDTASK, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->add_task_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->add_task_buffer_.getName(), "name");
  ASSERT_EQ(context_->add_task_buffer_.getLabel(), "");
  ASSERT_EQ(context_->add_task_buffer_.getPriority(), Priority::EMPTY);
  ASSERT_EQ(context_->add_task_buffer_.getDate(), boost::gregorian::date{boost::gregorian::not_a_date_time});
  ASSERT_EQ(context_->add_task_buffer_.getParent(), 0);
}

TEST_F(TaskParamsTest, shouldNotAddTaskWithIncorrectParams) {
  EXPECT_CALL(*io_, input).Times(8).WillOnce(Return("name"))
      .WillOnce(Return(""))
      .WillOnce(Return("high"))
      .WillOnce(Return("some priority"))
      .WillOnce(Return("High"))
      .WillOnce(Return("some date"))
      .WillOnce(Return("800-8-8"))
      .WillOnce(Return("2010-10-10"));
  EXPECT_CALL(*io_, output).Times(8);
  EXPECT_CALL(*io_, outputWithBreak).Times(4);

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::ADDTASK, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->add_task_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->add_task_buffer_.getName(), "name");
  ASSERT_EQ(context_->add_task_buffer_.getLabel(), "");
  ASSERT_EQ(context_->add_task_buffer_.getPriority(), Priority::HIGH);
  ASSERT_EQ(context_->add_task_buffer_.getDate(), boost::gregorian::from_string("2010-10-10"));
  ASSERT_EQ(context_->add_task_buffer_.getParent(), 0);
}

TEST_F(TaskParamsTest, shouldAddSubtask) {
  auto task_dto_ = TaskDTO::create(1, "to eat", "beaf", Priority::HIGH, boost::gregorian::from_string("2012-9-14"), false);
  auto subtask_dto_ = TaskDTO::create(2, "feed the cat", "wiskas", Priority::MEDIUM, boost::gregorian::from_string("2012-9-14"), false);
  auto vectorToReturn = std::vector<TaskDTO>{};
  vectorToReturn.push_back(task_dto_);
  auto secondVectorToReturn = vectorToReturn;
  secondVectorToReturn.push_back(subtask_dto_);

  EXPECT_CALL(*io_, inputCommand).Times(4).WillOnce(Return("add"))
                                                .WillOnce(Return("show"))
                                                .WillOnce(Return("add_subtask"))
                                                .WillOnce(Return("exit"));

  EXPECT_CALL(*io_, input).Times(11).WillOnce(Return("to eat"))
                                          .WillOnce(Return("beaf"))
                                          .WillOnce(Return("High"))
                                          .WillOnce(Return("2012-9-14"))
                                          .WillOnce(Return("all"))
                                          .WillOnce(Return("no"))
                                          .WillOnce(Return("0"))
                                          .WillOnce(Return("feed the cat"))
                                          .WillOnce(Return("wiskas"))
                                          .WillOnce(Return("Medium"))
                                          .WillOnce(Return("2012-9-14"));

  EXPECT_CALL(*io_, outputWithBreak).Times(19);
  EXPECT_CALL(*io_, output).Times(11);

  EXPECT_CALL(*service_, addTask).Times(1).WillOnce(Return(OperationResult{ErrorCode::NO_ERRORS}));
  EXPECT_CALL(*service_, getAllTasks).Times(2).WillOnce(Return(vectorToReturn))
                                                    .WillOnce(Return(secondVectorToReturn));
  EXPECT_CALL(*service_, addSubtask).Times(1).WillOnce(Return(OperationResult{ErrorCode::NO_ERRORS}));

  StateMachine task_machine_ = StateMachine::create(StatesMachineType::MAIN, this->context_);
  auto result = task_machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->show_list_buffer_.getList().size(), 2);
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getName(), "to eat");
  ASSERT_EQ(context_->show_list_buffer_.getList()[1].getName(), "feed the cat");
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getID(), 1);
  ASSERT_EQ(context_->show_list_buffer_.getList()[1].getID(), 2);
}
