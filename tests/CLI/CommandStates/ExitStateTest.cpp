//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/CommandStates/ExitState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class ExitStateTest : public ::testing::Test {
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

TEST_F(ExitStateTest, shouldInput) {
  auto state = ExitState{};

  ASSERT_TRUE(state.input(io));
}

TEST_F(ExitStateTest, shouldOutput) {
  auto state = ExitState{};

  EXPECT_CALL(*io, outputWithBreak).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(ExitStateTest, shouldRun) {
  auto state = ExitState{};

  EXPECT_CALL(*io, outputWithBreak).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(ExitStateTest, shouldHaveCorrectStateType) {
  auto state = ExitState{};

  ASSERT_EQ(StateType::EXIT_STATE, state.getType());
}

TEST_F(ExitStateTest, shouldNotSwitchState) {
  auto state = ExitState{};

  ASSERT_EQ(nullptr, state.switchState());
}
