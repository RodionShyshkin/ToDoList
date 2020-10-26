//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <ParamStateMachine.h>
#include <ParamStateMachineFactory.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class ParamStateMachineTest : public ::testing::Test {
 public:
  void SetUp() override {
    auto service = std::make_shared<MockService>();
    auto io = std::make_shared<MockIO>();
    context_ = std::make_shared<Context>(
        service, io);

    params1_.push(StateType::TASK_ID_PARAM);
    params1_.push(StateType::FILENAME_PARAM);
  }

  void TearDown() override {

  }

 protected:
  std::queue<StateType> params1_;

  std::shared_ptr<Context> context_;
};

TEST_F(ParamStateMachineTest, shouldCreateByQueueAndContext) {
  auto queue = params1_;
  ASSERT_NO_THROW(ParamStateMachine::create(std::move(queue), context_));
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithEmptyQueue) {
  auto queue = std::queue<StateType>();
  auto machine = ParamStateMachine::create(std::move(queue), context_);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithCorrectInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::queue<StateType> queue;
  queue.push(StateType::TASK_NAME_PARAM);
  queue.push(StateType::TASK_LABEL_PARAM);
  queue.push(StateType::TASK_PRIORITY_PARAM);
  queue.push(StateType::TASK_DATE_PARAM);

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
                                  .WillOnce(testing::Return("label"))
                                  .WillOnce(testing::Return(""))
                                  .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(4);

  auto machine = ParamStateMachine::create(std::move(queue), context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithIncorrectInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::queue<StateType> queue;
  queue.push(StateType::TASK_NAME_PARAM);
  queue.push(StateType::TASK_LABEL_PARAM);
  queue.push(StateType::TASK_PRIORITY_PARAM);
  queue.push(StateType::TASK_DATE_PARAM);

  EXPECT_CALL(*io, input).Times(5).WillOnce(testing::Return(""))
      .WillOnce(testing::Return("name"))
      .WillOnce(testing::Return("label"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));

  EXPECT_CALL(*io, outputWithBreak).Times(1);
  EXPECT_CALL(*io, output).Times(5);

  auto machine = ParamStateMachine::create(std::move(queue), context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithAddTaskGraph) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
      .WillOnce(testing::Return("label"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));

  EXPECT_CALL(*io, output).Times(4);

  auto machine = ParamStateMachineFactory::AddTask::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithAddSubtaskGraph) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
      .WillOnce(testing::Return("label"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));

  EXPECT_CALL(*io, output).Times(4);

  auto machine = ParamStateMachineFactory::AddSubtask::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithShowListGraphWithoutLabel) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("week"))
      .WillOnce(testing::Return("yes"));

  EXPECT_CALL(*io, output).Times(2);

  auto machine = ParamStateMachineFactory::ShowTasksList::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithShowListGraphWithLabel) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(3).WillOnce(testing::Return("by_label"))
      .WillOnce(testing::Return("yes"))
      .WillOnce(testing::Return("sample label"));

  EXPECT_CALL(*io, output).Times(3);

  auto machine = ParamStateMachineFactory::ShowTasksList::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithGetTaskGraph) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> list;
  list.push_back(TaskDTO::create(1, "name", "label", Priority::HIGH,
                                 boost::gregorian::date{2019-2-1},
                                 true));
  context->show_list_buffer_.setList(list);

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("21"))
                                      .WillOnce(testing::Return("0"));

  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(1);

  auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithPostponeGraph) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("adlkjfh"))
      .WillOnce(testing::Return("2020-10-10"));

  EXPECT_CALL(*io, output).Times(2);
  EXPECT_CALL(*io, outputWithBreak).Times(1);

  auto machine = ParamStateMachineFactory::PostponeTask::create(context);
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(ParamStateMachineTest, shouldWorkCorrectlyWithPersistGraph) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdfas.txt"));

  EXPECT_CALL(*io, output).Times(1);

  auto machine = ParamStateMachineFactory::PersistTasks::create(context);
  ASSERT_NO_THROW(machine.execute());
}