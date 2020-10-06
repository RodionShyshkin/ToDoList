//
// Created by rodion on 9/19/20.
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

  MOCK_METHOD(OperationResult<StorageError>, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, addSubtask, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(bool, postponeTask, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(bool, completeTask, (const unsigned int&), (override));

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

 class StateMachineTest : public ::testing::Test {
  public:

   void SetUp() override {
     this->io_ = std::make_shared<MockIO>();
     this->service_ = std::make_shared<MockService>();

     this->context_ = std::make_shared<Context>(this->service_, this->io_);

     this->first_type_ = StatesMachineType::GET_TASKS_LIST;
     this->second_type_ = StatesMachineType::MAIN;
   }

   void TearDown() override {

   }

  protected:
   std::shared_ptr<MockIO> io_;
   std::shared_ptr<MockService> service_;
   std::shared_ptr<Context> context_;

  protected:
   StatesMachineType first_type_;
   StatesMachineType second_type_;
   StatesMachineType third_type_;
   StatesMachineType fourth_type_;
   StatesMachineType all_type_;
 };

TEST_F(StateMachineTest, shouldWorkWithoutInternalStateMachines) {
  EXPECT_CALL(*io_, input).Times(2).WillOnce(Return("all"))
                                        .WillOnce(Return("yes"));
  EXPECT_CALL(*io_, output).Times(2);
  StateMachine machine_ = StateMachine::create(first_type_, context_);
  machine_.execute();

  ASSERT_EQ(context_->show_list_buffer_.getSortedFlag(), true);
  ASSERT_EQ(context_->show_list_buffer_.getModifier(), ListModifier::ALL);
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
}

TEST_F(StateMachineTest, shouldWorkWithoutInternalStateMachinesWithAdditionalFilledParamLabel) {
  EXPECT_CALL(*io_, input).Times(3).WillOnce(Return("by_label"))
                                        .WillOnce(Return("yes"))
                                        .WillOnce(Return("label"));
  EXPECT_CALL(*io_, output).Times(3);
  StateMachine machine_ = StateMachine::create(first_type_, context_);
  machine_.execute();

  ASSERT_EQ(context_->show_list_buffer_.getSortedFlag(), true);
  ASSERT_EQ(context_->show_list_buffer_.getModifier(), ListModifier::BY_LABEL);
  ASSERT_EQ(context_->show_list_buffer_.getLabel(), "label");
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
}

TEST_F(StateMachineTest, shouldWorkWithoutInternalStateMachinesWithAdditionalUnfilledParamLabel) {
  EXPECT_CALL(*io_, input).Times(3).WillOnce(Return("by_label"))
      .WillOnce(Return("yes"))
      .WillOnce(Return(""));
  EXPECT_CALL(*io_, output).Times(3);

  StateMachine machine_ = StateMachine::create(first_type_, context_);
  auto result = machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->show_list_buffer_.getSortedFlag(), true);
  ASSERT_EQ(context_->show_list_buffer_.getModifier(), ListModifier::BY_LABEL);
  ASSERT_EQ(context_->show_list_buffer_.getLabel(), "");
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
}

TEST_F(StateMachineTest, shouldWorkWithIncorrectParams) {
  EXPECT_CALL(*io_, input).Times(3).WillOnce(Return("today"))
                                        .WillOnce(Return("hz"))
                                        .WillOnce(Return("no"));
  EXPECT_CALL(*io_, output).Times(3);
  EXPECT_CALL(*io_, outputWithBreak).Times(1);

  StateMachine machine_ = StateMachine::create(first_type_, context_);
  auto result = machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->show_list_buffer_.getModifier(), ListModifier::TODAY);
  ASSERT_EQ(context_->show_list_buffer_.getSortedFlag(), false);
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
}

TEST_F(StateMachineTest, shouldWorkWithInternalStateMachine) {
  EXPECT_CALL(*io_, inputCommand).Times(3).WillOnce(Return("add"))
                                              .WillOnce(Return("show"))
                                              .WillOnce(Return("exit"));

  auto dto_ = TaskDTO::create(1, "Task Name", "Task Label", Priority::LOW,
                              boost::gregorian::from_string("2012-9-14"), false);
  auto vectorToReturn = std::vector<TaskDTO>();
  vectorToReturn.push_back(dto_);

  EXPECT_CALL(*io_, input).Times(6).WillOnce(Return("Task Name"))
                                    .WillOnce(Return("Task Label"))
                                    .WillOnce(Return("Low"))
                                    .WillOnce(Return("2012-9-14"))
                                    .WillOnce(Return("all"))
                                    .WillOnce(Return("yes"));
  EXPECT_CALL(*io_, outputWithBreak).Times(13);
  EXPECT_CALL(*io_, output).Times(6);
  EXPECT_CALL(*service_, addTask).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*service_, getAllTasks).Times(1).WillOnce(Return(vectorToReturn));

  StateMachine machine_ = StateMachine::create(second_type_, context_);
  auto result = machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->show_list_buffer_.getList().size(), 1);
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getName(), "Task Name");
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getLabel(), "Task Label");
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getPriority(), Priority::LOW);
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].getDueDate(), boost::gregorian::from_string("2012-9-14"));
}
