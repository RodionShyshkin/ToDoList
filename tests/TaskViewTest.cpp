//
// Created by rodion on 8/4/20.
//
#include <gtest/gtest.h>
#include "TaskView.h"
#include "TaskService.h"

using testing::Eq;

class TaskViewTest : public testing::Test {

};

TEST_F(TaskViewTest, getTasksForToday) {
  DateTime now = getCurrentTime();

  TaskView task_view;
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours(), now.getMinutes())), 1));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 2", "test", Task::Priority::EMPTY, DateTime(now.getYear()+2, now.getMonth(), now.getDay(), now.getHours(), now.getMinutes())), 2));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth()+2, now.getDay(), now.getHours(), now.getMinutes())), 3));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 4", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay()+2, now.getHours(), now.getMinutes())), 4));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 5", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours()+2, now.getMinutes())), 5));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 6", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours(), now.getMinutes()+5)), 6));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 7", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours(), now.getMinutes())), 7));

  auto today_tasks = task_view.getTodayTasks();

  ASSERT_EQ(today_tasks.size(), 4);
  ASSERT_EQ(today_tasks[0].getID(), TaskID(1));
  ASSERT_EQ(today_tasks[1].getID(), TaskID(7));
  ASSERT_EQ(today_tasks[2].getID(), TaskID(6));
  ASSERT_EQ(today_tasks[3].getID(), TaskID(5));
}

TEST_F(TaskViewTest, getTasksForWeek) {
  DateTime now = getCurrentTime();

  TaskView task_view;
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay() + 7, now.getHours(), now.getMinutes())), 1));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay() + 8, now.getHours(), now.getMinutes())), 2));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 4", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours(), now.getMinutes())), 3));

  auto week_tasks = task_view.getWeekTasks();

  ASSERT_FALSE(week_tasks.empty());
}

TEST_F(TaskViewTest, sortByPriority) {
  TaskView task_view;
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 1));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 2", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 2));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 3));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 4", "test", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 4));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 5", "test", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 5));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 6", "test", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 6));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 7", "test", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 7));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 8", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 8));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 9", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 9));

  auto sorted = task_view.getTasksByPriority(Task::Priority::EMPTY);
  ASSERT_EQ(sorted.size(), 3);
  ASSERT_EQ(sorted[0].getID(), 1);
  ASSERT_EQ(sorted[1].getID(), 8);
  ASSERT_EQ(sorted[2].getID(), 9);

  sorted = task_view.getTasksByPriority(Task::Priority::LOW);
  ASSERT_EQ(sorted.size(), 2);
  ASSERT_EQ(sorted[0].getID(), 4);
  ASSERT_EQ(sorted[1].getID(), 7);

  sorted = task_view.getTasksByPriority(Task::Priority::MEDIUM);
  ASSERT_EQ(sorted.size(), 2);
  ASSERT_EQ(sorted[0].getID(), 5);
  ASSERT_EQ(sorted[1].getID(), 6);

  sorted = task_view.getTasksByPriority(Task::Priority::HIGH);
  ASSERT_EQ(sorted.size(), 2);
  ASSERT_EQ(sorted[0].getID(), 2);
  ASSERT_EQ(sorted[1].getID(), 3);
}

TEST_F(TaskViewTest, sortByLabel) {
  TaskView task_view;
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 1));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 2", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 2));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 3));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 4", "test", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 4));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 5", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 5));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 6", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 6));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 7", "test 2", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 7));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 8", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 8));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 9", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 9));

  auto sorted = task_view.getTasksByLabel("test");
  ASSERT_EQ(sorted.size(), 4);
  ASSERT_EQ(sorted[0].getID(), 1);
  ASSERT_EQ(sorted[1].getID(), 2);
  ASSERT_EQ(sorted[2].getID(), 3);
  ASSERT_EQ(sorted[3].getID(), 4);

  sorted = task_view.getTasksByLabel("test 2");
  ASSERT_EQ(sorted.size(), 5);
  ASSERT_EQ(sorted[0].getID(), 5);
  ASSERT_EQ(sorted[1].getID(), 6);
  ASSERT_EQ(sorted[2].getID(), 7);
  ASSERT_EQ(sorted[3].getID(), 8);
  ASSERT_EQ(sorted[4].getID(), 9);
}

TEST_F(TaskViewTest, sortByName) {
  TaskView task_view;
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 1));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 2", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 2));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)), 3));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 4));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 5));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)), 6));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test 2", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)), 7));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 8));
  task_view.addTask(std::make_shared<TaskEntity>(Task("Task 3", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)), 9));

  auto sorted = task_view.getTasksByName("Task 1");
  ASSERT_EQ(sorted.size(), 1);
  ASSERT_EQ(sorted[0].getID(), 1);

  sorted = task_view.getTasksByName("Task 2");
  ASSERT_EQ(sorted.size(), 1);
  ASSERT_EQ(sorted[0].getID(), 2);

  sorted = task_view.getTasksByName("Task 3");
  ASSERT_EQ(sorted.size(), 7);
  ASSERT_EQ(sorted[0].getID(), 3);
  ASSERT_EQ(sorted[1].getID(), 4);
  ASSERT_EQ(sorted[2].getID(), 5);
  ASSERT_EQ(sorted[3].getID(), 6);
  ASSERT_EQ(sorted[4].getID(), 7);
  ASSERT_EQ(sorted[5].getID(), 8);
  ASSERT_EQ(sorted[6].getID(), 9);
}
