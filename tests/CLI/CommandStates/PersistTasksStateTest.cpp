//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/PersistTasksState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class PersistTasksStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(PersistTasksStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::SAVE};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(PersistTasksStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::LOAD};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(PersistTasksStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::SAVE};
  auto state2 = PersistTasksState{PersistType::LOAD};

  ASSERT_EQ(StateType::SAVE_TASKS, state.getType());
  ASSERT_EQ(StateType::LOAD_TASKS, state2.getType());
}

TEST_F(PersistTasksStateTest, shouldSaveCorrectly) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::SAVE};

  EXPECT_CALL(*service, Save).Times(1).WillOnce(testing::Return(
      OperationResult<PersistError>::Success()
  ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("filename.txt"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(PersistTasksStateTest, shouldLoadCorrectly) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::LOAD};

  EXPECT_CALL(*service, Load).Times(1).WillOnce(testing::Return(
      OperationResult<PersistError>::Success()
  ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("filename.txt"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}


TEST_F(PersistTasksStateTest, shouldNotSaveIfPersistError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::SAVE};

  EXPECT_CALL(*service, Save).Times(1).WillOnce(testing::Return(
      OperationResult<PersistError>::Fail(PersistError::SAVE_ERROR)
  ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("filename.txt"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(PersistTasksStateTest, shouldNotLoadIfPersistError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PersistTasksState{PersistType::LOAD};

  EXPECT_CALL(*service, Load).Times(1).WillOnce(testing::Return(
      OperationResult<PersistError>::Fail(PersistError::LOAD_ERROR)
  ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("filename.txt"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}


TEST_F(PersistTasksStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state1 = PersistTasksState{PersistType::SAVE};
  auto state2 = PersistTasksState{PersistType::LOAD};

  ASSERT_NE(nullptr, state1.switchState());
  ASSERT_NE(nullptr, state2.switchState());
}