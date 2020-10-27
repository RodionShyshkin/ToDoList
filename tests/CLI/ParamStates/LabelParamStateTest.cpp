//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/LabelParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class LabelParamStateTest : public ::testing::Test {
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

TEST_F(LabelParamStateTest, shouldInput) {
  auto state = LabelParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(LabelParamStateTest, shouldAcceptEmptyInput) {
  auto state = LabelParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(LabelParamStateTest, shouldOutput) {
  auto state = LabelParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(LabelParamStateTest, shouldHaveCorrectStateType) {
  auto state = LabelParamState{};

  ASSERT_EQ(StateType::TASK_LABEL_PARAM, state.getType());
}

TEST_F(LabelParamStateTest, shouldNotRunIfItIsParamOfShowListAll) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::Create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setList(tasks);

  auto state = LabelParamState{};

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
}

TEST_F(LabelParamStateTest, shouldRunIfItIsParamOfShowListByLabel) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::Create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::BY_LABEL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setList(tasks);

  auto state = LabelParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("label"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->show_list_buffer_.getLabel(), "label");
}

TEST_F(LabelParamStateTest, shouldRunIfItIsParamOfAddSubtaskWhenListOpen) {
  std::vector<TaskDTO> tasks;
  tasks.push_back(TaskDTO::Create(1, "name", "label", Priority::LOW,
                                  boost::gregorian::date{boost::gregorian::not_a_date_time},
                                  false));

  context->show_list_buffer_.setModifier(ListModifier::BY_LABEL);
  context->show_list_buffer_.setSortedFlag(true);
  context->show_list_buffer_.setLabel("label");
  context->show_list_buffer_.setList(tasks);

  context->id_buffer_.setID(1);

  auto state = LabelParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("label"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->add_task_buffer_.getLabel(), "label");
}

TEST_F(LabelParamStateTest, shouldNotSwitchState) {
  auto state = LabelParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}