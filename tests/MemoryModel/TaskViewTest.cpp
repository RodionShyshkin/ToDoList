//
// Created by rodion on 8/4/20.
//
#include <gtest/gtest.h>
#include <MemoryModel/TaskView.h>

class TaskViewTest : public ::testing::Test {
 public:
  TaskView task_view_;
  TaskEntity entity_ = TaskEntity::create(Task::create("Task", "test", Priority::EMPTY,
                                                       Date(2011, 2, 3)), 1);
  std::shared_ptr<TaskEntity> ptr = std::make_shared<TaskEntity>(entity_);
};

TEST_F(TaskViewTest, addTask) {
  EXPECT_NO_THROW(task_view_.AddTask(ptr));
}

TEST_F(TaskViewTest, getAllTasks) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(TaskViewTest, getTasksForToday) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTodayTasks();
  ASSERT_TRUE(tasks.empty());
}

TEST_F(TaskViewTest, getTasksForWeek) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetWeekTasks();
  ASSERT_TRUE(tasks.empty());
}

TEST_F(TaskViewTest, getTasksByLabel) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTasksByLabel("test");
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(TaskViewTest, getTasksByName) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTasksByName("Task");
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(TaskViewTest, getTasksByPriority) {
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTasksByPriority(Priority::EMPTY);
  ASSERT_EQ(tasks.size(), 1);
}

