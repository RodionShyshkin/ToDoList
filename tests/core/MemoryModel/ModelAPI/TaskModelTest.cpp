//
// Created by rodion on 10/1/20.
//

#include <MemoryModel/ModelAPI/TaskModel.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <API/TaskServiceInterface.h>
#include <Mocks/MockStorage.h>
#include <Mocks/MockView.h>
#include <Mocks/MockGenerator.h>
#include <MemoryModel/ModelAPI/ModelTaskDTOConverter.h>

using ::testing::Return;

class TaskModelTest : public ::testing::Test {
 public:
  void SetUp() override {
    task_without_name_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "", "label",
                                                           Priority::HIGH, Date{2020, 10, 10}, false);
    task_without_label_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "name", "",
                                                            Priority::HIGH, Date{2020, 10, 10}, false);
    task_without_priority_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "name", "label",
                                                               Priority::EMPTY, Date{2020, 10, 10}, false);
    task_without_date_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "name", "label",
                                                           Priority::HIGH,
                                                           Date{boost::gregorian::date{
                                                               boost::gregorian::not_a_date_time}},
                                                           false);

    simple_task_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "name", "label",
                                                     Priority::MEDIUM, Date{2020, 10, 10}, true);

    simple_subtask_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "subname", "label", Priority::MEDIUM,
                                                        Date{2020, 10, 10}, false);

    simple_entity_subtask_ = TaskEntity::createTask(Task::create(simple_task_.GetName(), simple_task_.GetLabel(),
                                                                 simple_task_.GetPriority(), simple_task_.GetDueDate()).value(),
                                                    simple_task_.GetID());


    parent_task_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "Michael", "label", Priority::MEDIUM,
                                                     Date{2020, 10, 10}, false);

    parent_entity_ = std::make_shared<TaskEntity>(TaskEntity::createTask(Task::create(parent_task_.GetName(),
                                                                                      parent_task_.GetLabel(),
                                                                                      parent_task_.GetPriority(),
                                                                                      parent_task_.GetDueDate()).value(),
                                                    TaskID{1}));
    parent_subtask_ =
        ModelTaskDTO::CreateWithoutParent(TaskID{1}, "John, subtask of Michael", "label", Priority::MEDIUM,
                                          Date{2020, 10, 10}, false);

    parent_sub_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(parent_subtask_.GetName(),
                                                                                             parent_subtask_.GetLabel(),
                                                                                             parent_subtask_.GetPriority(),
                                                                                             parent_subtask_.GetDueDate()).value(),
                                                    TaskID{2}, parent_entity_->GetID()));

    subtask1_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "George, subtask of John", "label", Priority::MEDIUM,
                                                  Date{2020, 10, 10}, false);

    subtask1_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask1_.GetName(),
                                                                                           subtask1_.GetLabel(),
                                                                                           subtask1_.GetPriority(),
                                                                                           subtask1_.GetDueDate()).value(),
                                                    TaskID{3}, parent_sub_entity_->GetID()));

    subtask2_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "Carl, subtask of John", "label", Priority::MEDIUM,
                                                  Date{2020, 10, 10}, false);

    subtask2_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask2_.GetName(),
                                                                                           subtask2_.GetLabel(),
                                                                                           subtask2_.GetPriority(),
                                                                                           subtask2_.GetDueDate()).value(),
                                                 TaskID{4}, parent_sub_entity_->GetID()));

    subtask11_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "Lawrence, subtask of George", "label", Priority::MEDIUM,
                                                   Date{2020, 10, 10}, false);

    subtask11_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask11_.GetName(),
                                                                                            subtask11_.GetLabel(),
                                                                                            subtask11_.GetPriority(),
                                                                                            subtask11_.GetDueDate()).value(),
                                                    TaskID{5}, subtask1_entity_->GetID()));

    subtask111_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "Diego, subtask of Lawrence", "label", Priority::MEDIUM,
                                                    Date{2020, 10, 10}, false);

    subtask111_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask111_.GetName(),
                                                                                             subtask111_.GetLabel(),
                                                                                             subtask111_.GetPriority(),
                                                                                             subtask111_.GetDueDate()).value(),
                                                  TaskID{6}, subtask11_entity_->GetID()));

    subtask112_ = ModelTaskDTO::CreateWithoutParent(TaskID{1}, "Arnold, subtask of Lawrence", "label", Priority::MEDIUM,
                                                    Date{2020, 10, 10}, false);

    subtask112_entity_ = std::make_shared<TaskEntity>(TaskEntity::createSubtask(Task::create(subtask112_.GetName(),
                                                                                             subtask112_.GetLabel(),
                                                                                             subtask112_.GetPriority(),
                                                                                             subtask112_.GetDueDate()).value(),
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

  OperationResult<StorageError> result = task_model.AddTask(task_without_name_);

  ASSERT_EQ(result.GetError(), StorageError::INVALID_TASK);
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
  ASSERT_EQ(result.GetError(), std::nullopt);

  result = task_model.AddTask(task_without_priority_);
  ASSERT_EQ(result.GetError(), std::nullopt);

  result = task_model.AddTask(task_without_date_);
  ASSERT_EQ(result.GetError(), std::nullopt);
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

  EXPECT_CALL(*storage, RemoveTask).Times(6).WillRepeatedly(Return(true));
  EXPECT_CALL(*view, AddTask).Times(7).WillRepeatedly(Return(true));
  EXPECT_CALL(*view, RemoveTask).Times(6).WillRepeatedly(Return(true));
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

  auto result = model.CompleteTask(2);

  ASSERT_TRUE(result);
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

  auto result = model.CompleteTask(1);

  ASSERT_FALSE(result);
}

TEST_F(TaskModelTest, shouldCompleteTaskWhichIsCompleted) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();


  parent_entity_->SetComplete();
  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(parent_entity_));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.CompleteTask(1);
  ASSERT_TRUE(result);
}

TEST_F(TaskModelTest, shouldPostponeCorrectTask) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(subtask1_entity_));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.PostponeTask(1, Date{2020, 12, 31});

  ASSERT_TRUE(result);
}

TEST_F(TaskModelTest, shouldNotPostponeUnexistingTask) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(nullptr));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.PostponeTask(1, Date{2020, 12, 31});

  ASSERT_FALSE(result);
}

TEST_F(TaskModelTest, getAllTasks) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);
  vectorToReturn.push_back(*subtask1_entity_);
  vectorToReturn.push_back(*parent_entity_);

  EXPECT_CALL(*storage, GetAllTasks).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetAllTasks();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].GetName(), "name");
  ASSERT_EQ(result[1].GetName(), "George, subtask of John");
  ASSERT_EQ(result[2].GetName(), "Michael");
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

  auto result = model.GetTasksForToday();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].GetName(), "name");
  ASSERT_EQ(result[1].GetName(), "George, subtask of John");
  ASSERT_EQ(result[2].GetName(), "Michael");
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

  auto result = model.GetTasksForWeek();

  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].GetName(), "name");
  ASSERT_EQ(result[1].GetName(), "George, subtask of John");
  ASSERT_EQ(result[2].GetName(), "Michael");
}

TEST_F(TaskModelTest, getTasksByLabel) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByLabel).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetTasksByLabel("name");

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].GetName(), "name");
}

TEST_F(TaskModelTest, getTasksByName) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByName).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetTasksByName("name");

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].GetName(), "name");
}

TEST_F(TaskModelTest, getTasksByPriority) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();
  std::vector<TaskEntity> vectorToReturn;
  vectorToReturn.push_back(simple_entity_subtask_);

  EXPECT_CALL(*view, GetTasksByPriority).Times(1).WillOnce(Return(vectorToReturn));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetTasksByPriority(Priority::MEDIUM);

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].GetName(), "name");
}

TEST_F(TaskModelTest, shouldGetTaskCorrectly) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(parent_entity_));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetTask(TaskID{1});

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.value().GetID(), TaskID{1});
}

TEST_F(TaskModelTest, shouldNotGetTaskWhichDoesNotExist) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(nullptr));

  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  auto result = model.GetTask(TaskID{1});

  ASSERT_FALSE(result.has_value());
}

TEST_F(TaskModelTest, shouldGetSubtasksCorrectly) {
  auto view = std::make_unique<MockView>();
  auto storage = std::make_unique<MockStorage>();
  auto generator = std::make_unique<MockGenerator>();

  parent_entity_->AddSubtask(subtask1_entity_);
  EXPECT_CALL(*storage, GetTask).Times(1).WillOnce(Return(parent_entity_));


  TaskModel model{std::move(storage), std::move(view), std::move(generator)};

  std::vector<ModelTaskDTO> result;
  ASSERT_NO_THROW(result = model.GetSubtasks(TaskID{1}));
  ASSERT_EQ(result.size(), 1);
}