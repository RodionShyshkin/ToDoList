//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/DateParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class DateParamStateTest : public ::testing::Test {
 public:
  void SetUp() override {
    auto service = std::make_shared<MockService>();
    io = std::make_shared<MockIO>();
    context = std::make_shared<Context>(
        service, io);
  }

  void TearDown() override {

  }

 protected:
  std::shared_ptr<MockIO> io;
  std::shared_ptr<Context> context;
};

TEST_F(DateParamStateTest, shouldAcceptCorrectInput) {
  auto state = DateParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("2020-10-10"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(DateParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = DateParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(DateParamStateTest, shouldAcceptEmptyInput) {
  auto state = DateParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(DateParamStateTest, shouldOutput) {
  auto state = DateParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(DateParamStateTest, shouldHaveCorrectStateType) {
  auto state = DateParamState{};

  ASSERT_EQ(StateType::TASK_DATE_PARAM, state.getType());
}

TEST_F(DateParamStateTest, shouldRunCorrectlyWhileAddTask) {
  auto state = DateParamState{};

  context->add_task_buffer_.setName("some name");
  context->add_task_buffer_.setLabel("some label");
  context->add_task_buffer_.setPriority(Priority::MEDIUM);

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("2020-10-10"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->add_task_buffer_.getDate(), boost::gregorian::date{
    boost::gregorian::from_string("2020-10-10")});
  ASSERT_EQ(context->postpone_buffer_.getNewDate(), boost::gregorian::date{
      boost::gregorian::not_a_date_time
  });
}

TEST_F(DateParamStateTest, shouldRunCorrectlyWhilePostponeTask) {
  auto state = DateParamState{};

  context->id_buffer_.setID(1);

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("2020-10-10"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->postpone_buffer_.getNewDate(), boost::gregorian::date{
      boost::gregorian::from_string("2020-10-10")});
  ASSERT_TRUE(context->postpone_buffer_.checkBufferFullness());
  ASSERT_EQ(context->add_task_buffer_.getDate(), boost::gregorian::date{
    boost::gregorian::not_a_date_time
  });
}


TEST_F(DateParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = DateParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("kmas"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
}

TEST_F(DateParamStateTest, shouldNotSwitchState) {
  auto state = DateParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
