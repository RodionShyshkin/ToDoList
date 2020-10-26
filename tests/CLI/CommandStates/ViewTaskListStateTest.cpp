//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/ViewTaskListState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class ViewTaskListStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(ViewTaskListStateTest, ShouldNotAcceptIncorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ViewTaskListStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(ViewTaskListStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};

  ASSERT_EQ(StateType::SHOW_TASKS_LIST, state.getType());
}

TEST_F(ViewTaskListStateTest, ShouldNotAcceptCommandFromOtherMenu) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ViewTaskListStateTest, ShouldAcceptCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add_subtask"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(ViewTaskListStateTest, shouldRunCorrectlyIfVectorIsNotEmpty) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getAllTasks).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("all"))
                                      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ViewTaskListStateTest, shouldNotRunIfVectorIsEmpty) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getAllTasks).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("all"))
                                      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::INCORRECT_INPUT);
}

TEST_F(ViewTaskListStateTest, shouldNotRunSuccessIfCommandIsIncorrect) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getAllTasks).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("all"))
      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::INCORRECT_INPUT);
}

TEST_F(ViewTaskListStateTest, ShouldNotSwitchStateIfThereAreNoCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = ViewTaskListState{};
  ASSERT_EQ(nullptr, state.switchState());
}

TEST_F(ViewTaskListStateTest, ShouldSwitchStateIfThereIsCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getAllTasks).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("all"))
      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  state.run(context);

  ASSERT_NE(nullptr, state.switchState());
}

TEST_F(ViewTaskListStateTest, shouldRunCorrectlyWithTodayModifier) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getTasksForToday).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("today"))
      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ViewTaskListStateTest, shouldRunCorrectlyWithWeekModifier) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getTasksForWeek).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("week"))
      .WillOnce(testing::Return("no"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ViewTaskListStateTest, shouldRunCorrectlyWithLabelModifier) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  auto dto = TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                             boost::gregorian::date{boost::gregorian::not_a_date_time},
                             true);
  vector.push_back(dto);

  auto state = ViewTaskListState{};

  EXPECT_CALL(*service, getTasksByLabel).Times(1).WillOnce(testing::Return(vector));

  EXPECT_CALL(*io, input).Times(3).WillOnce(testing::Return("by_label"))
      .WillOnce(testing::Return("no"))
      .WillOnce(testing::Return("label"));
  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("complete"));
  EXPECT_CALL(*io, output).Times(3);
  EXPECT_CALL(*io, outputWithBreak).Times(5);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}