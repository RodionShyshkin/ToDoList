//
// Created by rodion on 7/25/20.
//


#include <gtest/gtest.h>
#include "MemoryModel/Task/TaskEntity.h"

 class TaskEntityTest : public ::testing::Test {
 public:
  void SetUp() override {
    Task undertaskOne = Task::create("Task", "test", Priority::EMPTY,
                                     Date{2020, 10, 10}).value();
    Task undertaskTwo = Task::create("Subtask", "test", Priority::HIGH,
                                     Date{2090, 1, 1}).value();

    task = TaskEntity::createTask(undertaskOne, TaskID{1});
    subtask = TaskEntity::createSubtask(undertaskTwo, TaskID{2}, TaskID{1});
  }

  void TearDown() override {
    task = TaskEntity{};
    subtask = TaskEntity{};
  }

  TaskEntity task;
  TaskEntity subtask;
};

TEST_F(TaskEntityTest, shouldCreateTaskCorrectly) {
  Task task = Task::create("Task", "label",
                           Priority::LOW,
                           Date{2019, 1, 1}).value();
  TaskEntity task_entity;
  ASSERT_NO_THROW(task_entity = TaskEntity::createTask(task, TaskID{1}));
}

TEST_F(TaskEntityTest, shouldCreateSubtaskCorrectly) {
  Task task = Task::create("Task", "label",
                           Priority::LOW,
                           Date{2019, 1, 1}).value();
  TaskEntity task_entity;
  ASSERT_NO_THROW(task_entity = TaskEntity::createSubtask(task, TaskID{1}, TaskID{2}));
}

TEST_F(TaskEntityTest, Getters) {
  ASSERT_EQ(task.GetName(), "Task");
  ASSERT_EQ(task.GetLabel(), "test");
  ASSERT_EQ(task.GetPriority(), Priority::EMPTY);
  ASSERT_EQ(task.GetDueTime().GetDate(), Date(2020, 10, 10).GetDate());
  ASSERT_EQ(task.GetID(), 1);
  ASSERT_FALSE(task.GetStatus());
  EXPECT_NO_THROW(task.GetTask());
  EXPECT_NO_THROW(task.GetSubtasks());
}

TEST_F(TaskEntityTest, AddSubtask) {
  ASSERT_EQ(task.GetSubtasks().size(), 0);
  task.AddSubtask(std::make_shared<TaskEntity>(subtask));

  auto subtasks = task.GetSubtasks();
  ASSERT_EQ(subtasks.size(), 1);
  ASSERT_TRUE(subtasks.find(2) != subtasks.end());
}

TEST_F(TaskEntityTest, defaultConstructor) {
  EXPECT_NO_THROW(TaskEntity{});
}

TEST_F(TaskEntityTest, shouldAddSubtaskCorrectly) {
  ASSERT_NO_THROW(task.AddSubtask(std::make_shared<TaskEntity>(subtask)));
}

TEST_F(TaskEntityTest, shouldGetSubtasksCorrectly) {
  task.AddSubtask(std::make_shared<TaskEntity>(subtask));
  std::map<TaskID, std::weak_ptr<TaskEntity>> subtasks;
  ASSERT_NO_THROW(subtasks = task.GetSubtasks());
  ASSERT_EQ(subtasks.size(), 1);
}

TEST_F(TaskEntityTest, shouldReturnEmptyContainerIfThereAreNoSubtasks) {
  std::map<TaskID, std::weak_ptr<TaskEntity>> subtasks;
  ASSERT_NO_THROW(subtasks = task.GetSubtasks());
  ASSERT_EQ(subtasks.size(), 0);
}

TEST_F(TaskEntityTest, shouldRemoveSubtaskCorrectly) {
  task.AddSubtask(std::make_shared<TaskEntity>(subtask));
  auto subtasks = task.GetSubtasks();

  bool result;
  ASSERT_NO_THROW(result = task.RemoveSubtask(TaskID{2}));
  ASSERT_TRUE(result);
}

TEST_F(TaskEntityTest, shouldNotRemoveSubtaskIfItIsNotExist) {
  auto subtasks = task.GetSubtasks();

  bool result;
  ASSERT_NO_THROW(result = task.RemoveSubtask(TaskID{2}));
  ASSERT_FALSE(result);
}

TEST_F(TaskEntityTest, shouldCheckParentCorrectly) {
  task.AddSubtask(std::make_shared<TaskEntity>(subtask));
  ASSERT_TRUE(subtask.checkParent());
  ASSERT_FALSE(task.checkParent());
}