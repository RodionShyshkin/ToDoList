//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/IDParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class IDParamStateTest : public ::testing::Test {
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

TEST_F(IDParamStateTest, shouldNotAcceptNotNumberInput) {
  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(IDParamStateTest, shouldNotAcceptEmptyInput) {
  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(IDParamStateTest, shouldAcceptCorrectInput) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setList(tasks);

  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(IDParamStateTest, shouldOutput) {
  auto state = IDParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(IDParamStateTest, shouldHaveCorrectStateType) {
  auto state = IDParamState{};

  ASSERT_EQ(StateType::TASK_ID_PARAM, state.getType());
}

TEST_F(IDParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
}

TEST_F(IDParamStateTest, shouldNotRunIfTaskNotExist) {
  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("4"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
}

TEST_F(IDParamStateTest, shouldRunCorrectly) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setList(tasks);

  auto state = IDParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_TRUE(context->id_buffer_.checkBufferFullness());
  ASSERT_EQ(context->id_buffer_.getID(), 1);
}

TEST_F(IDParamStateTest, shouldNotSwitchState) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setList(tasks);

  auto state = IDParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
