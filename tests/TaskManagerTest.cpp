//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "../src/TaskManager.h"

using testing::Eq;

class TaskManagerTest : public testing::Test {

};

TEST_F(TaskManagerTest, uuid) {
  TaskManager dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir.addTask(Task("One", "first", Task::Priority::EMPTY, DateTime(2021, 8, 8, 8, 8)));
  dir.addTask(Task("Two", "second", Task::Priority::LOW, DateTime(2021, 8, 8, 8, 8)));
}
