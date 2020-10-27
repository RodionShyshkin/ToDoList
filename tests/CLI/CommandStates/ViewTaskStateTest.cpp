//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/ViewTaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class ViewTaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(ViewTaskStateTest, ShouldNotAcceptIncorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ViewTaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(ViewTaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};

  ASSERT_EQ(StateType::SHOW_TASK, state.getType());
}

TEST_F(ViewTaskStateTest, ShouldNotAcceptCommandFromOtherMenu) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ViewTaskStateTest, ShouldAcceptCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add_subtask"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(ViewTaskStateTest, shouldRunCorrectlyWithoutIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = ViewTaskState{};

  EXPECT_CALL(*service, GetTask).Times(1).WillOnce(testing::Return(
      std::make_optional<TaskDTO>(dto)));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(1);
  EXPECT_CALL(*io, outputWithBreak).Times(10);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ViewTaskStateTest, shouldRunCorrectlyWithIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto dto = TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  context->id_buffer_.setID(1);

  auto state = ViewTaskState{};

  EXPECT_CALL(*service, GetTask).Times(1).WillOnce(testing::Return(
      std::make_optional<TaskDTO>(dto)));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, outputWithBreak).Times(10);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ViewTaskStateTest, shouldNotRunIfOperationError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  vector.push_back(TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                                   boost::gregorian::date{2020 - 10 - 10}, true));

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = ViewTaskState{};

  EXPECT_CALL(*service, GetTask).Times(1).WillOnce(testing::Return(std::nullopt));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(ViewTaskStateTest, shouldNotRunSuccessIfCommandIsIncorrect) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto dto = TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  context->id_buffer_.setID(1);

  auto state = ViewTaskState{};

  EXPECT_CALL(*service, GetTask).Times(1).WillOnce(testing::Return(
      std::make_optional<TaskDTO>(dto)));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));
  EXPECT_CALL(*io, outputWithBreak).Times(10);

  ASSERT_EQ(state.run(context), StateResult::INCORRECT_INPUT);
}

TEST_F(ViewTaskStateTest, ShouldNotSwitchStateIfThereAreNoCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskState{};
  ASSERT_EQ(nullptr, state.switchState());
}

TEST_F(ViewTaskStateTest, ShouldSwitchStateIfThereIsCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto dto = TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  context->id_buffer_.setID(1);

  auto state = ViewTaskState{};

  EXPECT_CALL(*service, GetTask).Times(1).WillOnce(testing::Return(
      std::make_optional<TaskDTO>(dto)));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add_subtask"));
  EXPECT_CALL(*io, outputWithBreak).Times(10);

  state.run(context);

  ASSERT_NE(nullptr, state.switchState());
}
