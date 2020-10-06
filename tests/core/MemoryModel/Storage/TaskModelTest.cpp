//
// Created by rodion on 10/1/20.
//

#include <src/core/MemoryModel/CoreAPI/TaskModel.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <src/core/API/TaskServiceInterface.h>

using ::testing::Return;

class MockView : public TaskViewInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::weak_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetTodayTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetWeekTasks, (), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetAllTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByLabel, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByName, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByPriority, (const Priority&), (override));
};

class MockStorage : public TaskStorageInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::shared_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));
  MOCK_METHOD(std::shared_ptr<TaskEntity>, GetTask, (const TaskID&), (override));
};

class MockGenerator : public IDGeneratorInterface {
 public:
  MOCK_METHOD(TaskID, GenerateID, (), (override));
};

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(TaskDTO, getTask, (const unsigned int&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult<StorageError>, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, addSubtask, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(OperationResult<StorageError>, postponeTask, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(OperationResult<StorageError>, completeTask, (const unsigned int&), (override));

  MOCK_METHOD(OperationResult<SerializationError>, SaveToFile, (const std::string&), (override));
  MOCK_METHOD(OperationResult<SerializationError>, LoadFromFile, (const std::string&), (override));
};

class TaskModelTest : public ::testing::Test {
 public:
  void SetUp() override {
    task_without_name_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "", "label",
                                                           Priority::HIGH, Date{2020, 10, 10}, false);
    task_without_label_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "name", "",
                                                            Priority::HIGH, Date{2020, 10, 10}, false);
    task_without_priority_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "name", "label",
                                                               Priority::EMPTY, Date{2020, 10, 10}, false);
    task_without_date_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "name", "label",
                                                           Priority::HIGH,
                                                           Date{boost::gregorian::date{boost::gregorian::not_a_date_time}},
                                                           false);

    simple_task_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "name", "label",
                                                     Priority::MEDIUM, Date{2020, 10, 10}, true);

    simple_subtask_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "subname", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    simple_entity_subtask_ = TaskEntity::createTask(Task::create(simple_task_.getName(), simple_task_.getLabel(),
                                                                 simple_task_.getPriority(), simple_task_.getDueDate()).value(),
                                                    simple_task_.getID());


    parent_task_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "Michael", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    parent_entity_ = std::make_shared<TaskEntity>(TaskEntity::createTask(Task::create(parent_task_.getName(), parent_task_.getLabel(),
                                                                 parent_task_.getPriority(), parent_task_.getDueDate()).value(),
                                                    TaskID{1}));
    parent_subtask_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "John, subtask of Michael", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    parent_sub_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(parent_subtask_.getName(), parent_subtask_.getLabel(),
                                                                 parent_subtask_.getPriority(), parent_subtask_.getDueDate()).value(),
                                                    TaskID{2}, parent_entity_->GetID()));

    subtask1_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "George, subtask of John", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    subtask1_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask1_.getName(), subtask1_.getLabel(),
                                                                 subtask1_.getPriority(), subtask1_.getDueDate()).value(),
                                                    TaskID{3}, parent_sub_entity_->GetID()));

    subtask2_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "Carl, subtask of John", "label", Priority::MEDIUM,
                                                  Date{2020, 10, 10}, false);

    subtask2_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask2_.getName(), subtask2_.getLabel(),
                                                              subtask2_.getPriority(), subtask2_.getDueDate()).value(),
                                                 TaskID{4}, parent_sub_entity_->GetID()));

    subtask11_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "Lawrence, subtask of George", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    subtask11_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask11_.getName(), subtask11_.getLabel(),
                                                                 subtask11_.getPriority(), subtask11_.getDueDate()).value(),
                                                    TaskID{5}, subtask1_entity_->GetID()));

    subtask111_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "Diego, subtask of Lawrence", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    subtask111_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask111_.getName(), subtask111_.getLabel(),
                                                               subtask111_.getPriority(), subtask111_.getDueDate()).value(),
                                                  TaskID{6}, subtask11_entity_->GetID()));

    subtask112_ = ModelTaskDTO::createWithoutParent(TaskID{1}, "Arnold, subtask of Lawrence", "label", Priority::MEDIUM,
                                                    Date{2020, 10, 10}, false);

    subtask112_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask112_.getName(), subtask112_.getLabel(),
                                                                subtask112_.getPriority(), subtask112_.getDueDate()).value(),
                                                   TaskID{7}, subtask11_entity_->GetID()));
  }

  void TearDown() override {

  }

 protected:
  ModelTaskDTO task_without_name_;
  ModelTaskDTO task_without_label_;
  ModelTaskDTO task_without_date_;
  ModelTaskDTO task_without_priority_;
  ModelTaskDTO simple_task_;
  ModelTaskDTO simple_subtask_;

  ModelTaskDTO parent_task_;
  ModelTaskDTO parent_subtask_;
  ModelTaskDTO subtask1_;
  ModelTaskDTO subtask2_;
  ModelTaskDTO subtask11_;
  ModelTaskDTO subtask111_;
  ModelTaskDTO subtask112_;

  TaskEntity simple_entity_subtask_;

  std::shared_ptr<TaskEntity> parent_entity_;
  std::shared_ptr<TaskEntity> parent_sub_entity_;
  std::shared_ptr<TaskEntity> subtask1_entity_;
  std::shared_ptr<TaskEntity> subtask2_entity_;
  std::shared_ptr<TaskEntity> subtask11_entity_;
  std::shared_ptr<TaskEntity> subtask111_entity_;
  std::shared_ptr<TaskEntity> subtask112_entity_;
};

TEST_F(TaskModelTest, shouldNotAddTaskWithoutName) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  TaskModel task_model(std::move(storage), std::move(view), std::move(generator));
  auto rhs_result = OperationResult<StorageError>{StorageError::INVALID_TASK};

  OperationResult<StorageError> result = task_model.AddTask(task_without_name_);

  ASSERT_EQ(result.GetError(), rhs_result.GetError());
}

TEST_F(TaskModelTest, shouldAddWithoutOtherParams) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*view, AddTask).Times(3).WillRepeatedly(Return(true));
  EXPECT_CALL(*storage, AddTask).Times(3).WillRepeatedly(Return(true));
  EXPECT_CALL(*generator, GenerateID).Times(3).WillOnce(Return(TaskID{1}))
                                                  .WillOnce(Return(TaskID{2}))
                                                  .WillOnce(Return(TaskID{3}));

  TaskModel task_model(std::move(storage), std::move(view), std::move(generator));

  OperationResult<StorageError> result = task_model.AddTask(task_without_label_);
  ASSERT_TRUE(result.GetStatus());

  result = task_model.AddTask(task_without_priority_);
  ASSERT_TRUE(result.GetStatus());

  result = task_model.AddTask(task_without_date_);
  ASSERT_TRUE(result.GetStatus());
}

TEST_F(TaskModelTest, shouldNotAddTaskIfStorageCannotDoIt) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, AddTask).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*generator, GenerateID).Times(1).WillOnce(Return(TaskID{1}));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.AddTask(simple_task_);

  ASSERT_EQ(result.GetError(),  StorageError::WRONG_TASK_ID);
}

TEST_F(TaskModelTest, shouldNotAddTaskIfViewCannotDoIt) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, AddTask).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*view, AddTask).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*generator, GenerateID).Times(1).WillOnce(Return(TaskID{1}));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.AddTask(simple_task_);

  ASSERT_EQ(result.GetError(),  StorageError::WRONG_TASK_ID);
}

TEST_F(TaskModelTest, shouldAddSubtaskToATask) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, AddTask).Times(2).WillRepeatedly(Return(true));
  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(std::make_shared<TaskEntity>(simple_entity_subtask_)));
  EXPECT_CALL(*view, AddTask).Times(2).WillRepeatedly(Return(true));
  EXPECT_CALL(*generator, GenerateID).Times(2).WillOnce(Return(TaskID{1}))
                                              .WillOnce(Return(TaskID{2}));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  model.AddTask(simple_task_);
  auto result = model.AddSubtask(1, simple_subtask_);
  ASSERT_EQ(result.GetError(), std::nullopt);
}

TEST_F(TaskModelTest, shouldRemoveTaskWithSubtasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, AddTask).Times(7).WillRepeatedly(Return(true));
  EXPECT_CALL(*storage, GetTask).Times(18).WillOnce(Return(parent_entity_))
                                              .WillOnce(Return(parent_sub_entity_))
                                              .WillOnce(Return(parent_sub_entity_))
                                              .WillOnce(Return(subtask1_entity_))
                                              .WillOnce(Return(subtask11_entity_))
                                              .WillOnce(Return(subtask11_entity_))

                                              .WillOnce(Return(parent_sub_entity_))
                                              .WillOnce(Return(subtask1_entity_))
                                              .WillOnce(Return(subtask11_entity_))
                                              .WillOnce(Return(subtask111_entity_))
                                              .WillOnce(Return(subtask11_entity_))
                                              .WillOnce(Return(subtask112_entity_))
                                              .WillOnce(Return(subtask11_entity_))
                                              .WillOnce(Return(subtask1_entity_))
                                              .WillOnce(Return(parent_sub_entity_))
                                              .WillOnce(Return(subtask2_entity_))
                                              .WillOnce(Return(parent_sub_entity_))
                                              .WillOnce(Return(parent_entity_));

  EXPECT_CALL(*storage, RemoveTask).Times(11).WillRepeatedly(Return(true));
  EXPECT_CALL(*view, AddTask).Times(7).WillRepeatedly(Return(true));
  EXPECT_CALL(*view, RemoveTask).Times(11).WillRepeatedly(Return(true));
  EXPECT_CALL(*generator, GenerateID).Times(7).WillOnce(Return(TaskID{1}))
                                              .WillOnce(Return(TaskID{2}))
                                              .WillOnce(Return(TaskID{3}))
                                              .WillOnce(Return(TaskID{4}))
                                              .WillOnce(Return(TaskID{5}))
                                              .WillOnce(Return(TaskID{6}))
                                              .WillOnce(Return(TaskID{7}));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  model.AddTask(parent_task_);
  model.AddSubtask(1, parent_subtask_);
  model.AddSubtask(2, subtask1_);
  model.AddSubtask(2, subtask2_);
  model.AddSubtask(3, subtask11_);
  model.AddSubtask(5, subtask111_);
  model.AddSubtask(5, subtask112_);

  auto result = model.RemoveTask(2);

  ASSERT_EQ(result.GetError(), std::nullopt);
  ASSERT_EQ(parent_entity_->GetSubtasks().size(), 0);
}

TEST_F(TaskModelTest, shouldNotRemoveTaskWhichDoesNotExist) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(nullptr));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.RemoveTask(1);

  ASSERT_EQ(result.GetError(), StorageError::TASK_NOT_FOUND);
}

TEST_F(TaskModelTest, shouldCompleteTaskWithSubtasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, AddTask).Times(7).WillRepeatedly(Return(true));
  EXPECT_CALL(*storage, GetTask).Times(12).WillOnce(Return(parent_entity_))
      .WillOnce(Return(parent_sub_entity_))
      .WillOnce(Return(parent_sub_entity_))
      .WillOnce(Return(subtask1_entity_))
      .WillOnce(Return(subtask11_entity_))
      .WillOnce(Return(subtask11_entity_))

      .WillOnce(Return(parent_sub_entity_))
      .WillOnce(Return(subtask1_entity_))
      .WillOnce(Return(subtask11_entity_))
      .WillOnce(Return(subtask111_entity_))
      .WillOnce(Return(subtask112_entity_))
      .WillOnce(Return(subtask2_entity_));

  EXPECT_CALL(*view, AddTask).Times(7).WillRepeatedly(Return(true));
  EXPECT_CALL(*generator, GenerateID).Times(7).WillOnce(Return(TaskID{1}))
      .WillOnce(Return(TaskID{2}))
      .WillOnce(Return(TaskID{3}))
      .WillOnce(Return(TaskID{4}))
      .WillOnce(Return(TaskID{5}))
      .WillOnce(Return(TaskID{6}))
      .WillOnce(Return(TaskID{7}));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  model.AddTask(parent_task_);
  model.AddSubtask(1, parent_subtask_);
  model.AddSubtask(2, subtask1_);
  model.AddSubtask(2, subtask2_);
  model.AddSubtask(3, subtask11_);
  model.AddSubtask(5, subtask111_);
  model.AddSubtask(5, subtask112_);


  EXPECT_FALSE(parent_entity_->GetStatus());
  EXPECT_FALSE(parent_sub_entity_->GetStatus());
  EXPECT_FALSE(subtask1_entity_->GetStatus());
  EXPECT_FALSE(subtask2_entity_->GetStatus());
  EXPECT_FALSE(subtask11_entity_->GetStatus());
  EXPECT_FALSE(subtask111_entity_->GetStatus());
  EXPECT_FALSE(subtask112_entity_->GetStatus());

  auto result = model.completeTask(2);

  ASSERT_EQ(result.GetError(), std::nullopt);
  ASSERT_EQ(parent_entity_->GetSubtasks().size(), 1);

  ASSERT_FALSE(parent_entity_->GetStatus());
  ASSERT_TRUE(parent_sub_entity_->GetStatus());
  ASSERT_TRUE(subtask1_entity_->GetStatus());
  ASSERT_TRUE(subtask2_entity_->GetStatus());
  ASSERT_TRUE(subtask11_entity_->GetStatus());
  ASSERT_TRUE(subtask111_entity_->GetStatus());
  ASSERT_TRUE(subtask112_entity_->GetStatus());
}

TEST_F(TaskModelTest, shouldNotCompleteTaskWhichDoesNotExist) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(nullptr));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.completeTask(1);

  ASSERT_EQ(result.GetError(), StorageError::TASK_NOT_FOUND);
}

TEST_F(TaskModelTest, shouldNotCompleteTaskWhichIsCompleted) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();


  parent_entity_->SetComplete();
  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(parent_entity_));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.completeTask(1);

  ASSERT_EQ(result.GetError(), StorageError::COMPLETED_TASK);
}

TEST_F(TaskModelTest, shouldPostponeCorrectTask) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(subtask1_entity_));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.postponeTask(1, Date{2020, 12, 31});

  ASSERT_EQ(result.GetError(), std::nullopt);
}

TEST_F(TaskModelTest, shouldNotPostponeUnexistingTask) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(nullptr));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.postponeTask(1, Date{2020, 12, 31});

  ASSERT_EQ(result.GetError(), StorageError::TASK_NOT_FOUND);
}

TEST_F(TaskModelTest, getAllTasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);
  vectorToReturn.push_back(*subtask1_entity_);
  vectorToReturn.push_back(*parent_entity_);

  EXPECT_CALL(*view, GetAllTasks).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getAllTasks();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].getName(), "name");
  ASSERT_EQ(result[1].getName(), "George, subtask of John");
  ASSERT_EQ(result[2].getName(), "Michael");
}

TEST_F(TaskModelTest, getTodayTasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);
  vectorToReturn.push_back(*subtask1_entity_);
  vectorToReturn.push_back(*parent_entity_);

  EXPECT_CALL(*view, GetTodayTasks).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getTasksForToday();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].getName(), "name");
  ASSERT_EQ(result[1].getName(), "George, subtask of John");
  ASSERT_EQ(result[2].getName(), "Michael");
}

TEST_F(TaskModelTest, getWeekTasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);
  vectorToReturn.push_back(*subtask1_entity_);
  vectorToReturn.push_back(*parent_entity_);

  EXPECT_CALL(*view, GetWeekTasks).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getTasksForWeek();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].getName(), "name");
  ASSERT_EQ(result[1].getName(), "George, subtask of John");
  ASSERT_EQ(result[2].getName(), "Michael");
}

TEST_F(TaskModelTest, getTasksByLabel) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByLabel).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getTasksByLabel("name");

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].getName(), "name");
}

TEST_F(TaskModelTest, getTasksByName) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByName).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getTasksByName("name");

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].getName(), "name");
}

TEST_F(TaskModelTest, getTasksByPriority) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByPriority).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.getTasksByPriority(Priority::MEDIUM);

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].getName(), "name");
}
