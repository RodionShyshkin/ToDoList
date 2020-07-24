//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "../src/GenerateID.h"
#include "../src/TaskManager.h"
#include "../src/TaskManagerDTO.h"

using testing::Eq;

class GenerateIDTest : public testing::Test {

};

TEST_F(GenerateIDTest, UserIDsGenerating) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);

  dir->addTask(Task("Name 1", "label", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir->addTask(Task("Name 2", "label", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir->addTask(Task("Name 3", "label", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  auto vec = check.getAllTasks();

  ASSERT_EQ(1, vec[0]->getUserID());
  ASSERT_EQ(2, vec[1]->getUserID());
  ASSERT_EQ(3, vec[2]->getUserID());

  dir->addSubtask(2, Task("Name 3", "label", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  vec = check.getAllTasks();

  ASSERT_EQ(4, vec[3]->getUserID());
}
