//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "taskID.h"
#include "TaskManager.h"

using testing::Eq;

class TaskIDTest : public testing::Test {

};

TEST_F(TaskIDTest, shouldIncreaseID) {
  unsigned int oldID = taskID::generateID();
  unsigned int newID = taskID::generateID();

  TaskManager dir;
  auto task1_ptr = std::make_shared<Task>(Task("Eating", "fish", Task::Priority::HIGH, DueTime(2019, 01, 01, 23, 0, 0)));
  auto task2_ptr = std::make_shared<Task>(Task("Cooking", "meat", Task::Priority::MEDIUM, DueTime(2019, 01, 01, 23, 10, 0)));
  auto fullTask1 = FullTask(task1_ptr);
  auto fullTask2 = FullTask(task2_ptr);
  dir.addTask(fullTask1);
  dir.addTask(fullTask2);

  ASSERT_EQ(fullTask1.getID() + 1, fullTask2.getID());
}

