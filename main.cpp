#include <iostream>
#include "src/Task.h"
#include "src/TaskManager.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  TaskManager dir;
  dir.addTask(FullTask(std::make_shared<Task>(Task("Eating", "fish", Task::Priority::HIGH, DueTime(2019, 01, 01, 23, 0, 0)))));
  dir.addTask(FullTask(std::make_shared<Task>(Task("Cooking", "meat", Task::Priority::MEDIUM, DueTime(2019, 01, 01, 23, 10, 0)))));


  return 0;
}
