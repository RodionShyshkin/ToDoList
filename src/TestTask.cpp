//
// Created by rodion on 7/16/20.
//

#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "Task.h"

using testing::Eq;

class TestTask : public testing::Test {

};

TEST_F(TestTask, shouldReturnFalse) {
  Task task("Name", "Label", Task::Priority::HIGH, DueTime(1945, 8, 9, 3, 1, 2));
  ASSERT_EQ(false, task.getStatus());
}

TEST_F(TestTask, shouldChangeStatusToOpposite) {
  Task task("Name", "Label", Task::Priority::HIGH, DueTime(1945, 8, 9, 3, 1, 2));
  bool oldstatus = task.getStatus();
  task.setStatus();
  ASSERT_NE(oldstatus, task.getStatus());
}

TEST_F(TestTask, shouldReturnNotEmptyString) {
  Task task("Name", "Label", Task::Priority::HIGH, DueTime(1945, 8, 9, 3, 1, 2));
  auto priority = task.showPriority();
  ASSERT_FALSE(priority.empty());
}

