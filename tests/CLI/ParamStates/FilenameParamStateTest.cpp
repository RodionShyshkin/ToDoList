//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/FilenameParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class FilenameParamStateTest : public ::testing::Test {
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

TEST_F(FilenameParamStateTest, shouldAcceptCorrectInput) {
  auto state = FilenameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asf"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(FilenameParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = FilenameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(FilenameParamStateTest, shouldOutput) {
  auto state = FilenameParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(FilenameParamStateTest, shouldHaveCorrectStateType) {
  auto state = FilenameParamState{};

  ASSERT_EQ(StateType::FILENAME_PARAM, state.getType());
}

TEST_F(FilenameParamStateTest, shouldRunCorrectly) {
  auto state = FilenameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("testfile.txt"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->filepath_buffer_.getFilepath(), "testfile.txt");
  ASSERT_TRUE(context->filepath_buffer_.checkBufferFullness());
}

TEST_F(FilenameParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = FilenameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
  ASSERT_EQ(context->filepath_buffer_.getFilepath(), "");
  ASSERT_FALSE(context->filepath_buffer_.checkBufferFullness());
}

TEST_F(FilenameParamStateTest, shouldNotSwitchState) {
  auto state = FilenameParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
