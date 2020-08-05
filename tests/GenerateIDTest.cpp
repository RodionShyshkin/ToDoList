//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "TaskService.h"

using testing::Eq;

class GenerateIDTest : public testing::Test {

};

TEST_F(GenerateIDTest, GenerateID) {
  TaskService service;
  service.addTask(Task("Name 1", "label", Task::Priority::HIGH, DateTime(2020, 10, 10, 10, 10)));
  service.addTask(Task("Name 2", "label", Task::Priority::HIGH, DateTime(2020, 10, 10, 10, 10)));
  service.addSubtask(2, Task("Name 3", "label", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));

  auto allTasks = service.getAllTasks();

  ASSERT_EQ(allTasks[0].getID(), 1);
  ASSERT_EQ(allTasks[1].getID(), 2);
  ASSERT_EQ(allTasks[2].getID(), 3);
}
