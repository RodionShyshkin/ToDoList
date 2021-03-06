//
// Created by rodion on 9/19/20.
//
/*
#include <StateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;



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
  EXPECT_CALL(*service_, add_task_graph).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*service_, GetAllTasks).Times(1).WillOnce(Return(vectorToReturn));

  StateMachine machine_ = StateMachine::Create(second_type_, context_);
  auto result = machine_.execute();

  ASSERT_EQ(result, true);
  ASSERT_EQ(context_->show_list_buffer_.checkBufferFullness(), true);
  ASSERT_EQ(context_->show_list_buffer_.getList().size(), 1);
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].GetName(), "Task Name");
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].GetLabel(), "Task Label");
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].GetPriority(), Priority::LOW);
  ASSERT_EQ(context_->show_list_buffer_.getList()[0].GetDueDate(), boost::gregorian::from_string("2012-9-14"));
}
*/