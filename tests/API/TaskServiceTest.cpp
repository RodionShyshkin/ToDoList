//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "API/TaskService.h"

 class TaskServiceTest : public ::testing::Test {
 public:
  TaskService service;
  Task task = Task::create("Task", "test", Priority::EMPTY, Date(2020, 10, 10));
  Task subtask = Task::create("Subtask", "test", Priority::EMPTY, Date(2020, 10, 10));
};

TEST_F(TaskServiceTest, getAllTasks) {
  EXPECT_NO_THROW(service.getAllTasks());
}

TEST_F(TaskServiceTest, addTask) {
  service.addTask(task);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(TaskServiceTest, addSubtask) {
  service.addTask(task);
  service.addSubtask(1, subtask);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 2);
}

TEST_F(TaskServiceTest, getTasksForToday) {
  EXPECT_NO_THROW(service.getTasksForToday());
}

TEST_F(TaskServiceTest, getTasksForWeek) {
  EXPECT_NO_THROW(service.getTasksForWeek());
}

TEST_F(TaskServiceTest, getTaskForLabel) {
  service.addTask(task);
  service.addSubtask(1, subtask);
  auto tasks = service.getTasksForLabel("test");
  ASSERT_EQ(tasks.size(), 2);
}
