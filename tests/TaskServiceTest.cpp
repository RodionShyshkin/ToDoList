//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "TaskService.h"

using testing::Eq;

class TaskServiceTest : public testing::Test {
};

TEST_F(TaskServiceTest, addTask) {
  TaskService service;

  service.addTask(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));

  auto tasksAmount = service.getAllTasks().size();
  auto task = service.getTaskByID(1);

  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ("Task", task.getName());
  ASSERT_EQ("test", task.getLabel());
  ASSERT_EQ(Task::Priority::EMPTY, task.getPriority());
  ASSERT_EQ(DueTime(DateTime(2020, 10, 10, 10, 10)), task.getDueTime());
  ASSERT_EQ(false, task.getStatus());
}

TEST_F(TaskServiceTest, addSubtask) {
  TaskService service;

  service.addTask(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  bool status_one = service.addSubtask(1, Task("Subtask 1", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  bool status_two = service.addSubtask(3, Task("Subtask 2", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));

  ASSERT_EQ(true, status_one);
  ASSERT_EQ(false, status_two);

  auto tasks = service.getAllTasks();
  ASSERT_EQ(2, tasks.size());
  ASSERT_EQ(tasks[0].getID(), 1);
  ASSERT_EQ(tasks[1].getID(), 2);
}

TEST_F(TaskServiceTest, getTasksForToday) {
  TaskService service;

  auto now = getCurrentTime();

  service.addTask(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), 18, 30)));
  service.addTask(Task("Task 2", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay() + 1, 18, 30)));
  service.addTask(Task("Task 3", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), 23, 59)));
  service.addTask(Task("Task 4", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth() + 1, now.getDay(), 23, 59)));

  auto today_tasks = service.getTasksForToday();

  ASSERT_EQ(2, today_tasks.size());
  ASSERT_EQ(today_tasks[0].getID(), 1);
  ASSERT_EQ(today_tasks[1].getID(), 3);
}

TEST_F(TaskServiceTest, getTasksForWeek) {
  TaskService service;

  auto now = getCurrentTime();
  service.addTask(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay() + 7, now.getHours(), now.getMinutes()).validateTime()));
  service.addTask(Task("Task 3", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay() + 8, now.getHours(), now.getMinutes()).validateTime()));
  service.addTask(Task("Task 4", "test", Task::Priority::EMPTY, DateTime(now.getYear(), now.getMonth(), now.getDay(), now.getHours(), now.getMinutes()).validateTime()));

  auto week_tasks = service.getTasksForWeek();
  ASSERT_FALSE(week_tasks.empty());
}

TEST_F(TaskServiceTest, getTaskForLabel) {
  TaskService service;

  service.addTask(Task("Task 1", "test", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 2", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)));

 /* bool operator< (const TaskID& task) {
    return this->id_ < task.get_id();
  }*/

/*  operator unsigned int() const {
    return id_;
  }*/
service.addTask(Task("Task 3", "test", Task::Priority::HIGH, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 4", "test", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 5", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 6", "test 2", Task::Priority::MEDIUM, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 7", "test 2", Task::Priority::LOW, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 8", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)));
  service.addTask(Task("Task 9", "test 2", Task::Priority::EMPTY, DateTime(2020, 1, 1, 1, 1)));

  auto sorted = service.getTasksForLabel("test");
  ASSERT_EQ(sorted.size(), 4);
  ASSERT_EQ(sorted[0].getID(), 1);
  ASSERT_EQ(sorted[1].getID(), 2);
  ASSERT_EQ(sorted[2].getID(), 3);
  ASSERT_EQ(sorted[3].getID(), 4);

  sorted = service.getTasksForLabel("test 2");
  ASSERT_EQ(sorted.size(), 5);
  ASSERT_EQ(sorted[0].getID(), 5);
  ASSERT_EQ(sorted[1].getID(), 6);
  ASSERT_EQ(sorted[2].getID(), 7);
  ASSERT_EQ(sorted[3].getID(), 8);
  ASSERT_EQ(sorted[4].getID(), 9);
}

TEST_F(TaskServiceTest, defaultConstructorDTO) {
  EXPECT_NO_THROW(TaskDTO());
}