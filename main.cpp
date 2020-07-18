#include <iostream>
#include "src/Task.h"
#include "src/TaskManager.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  TaskManager dir;

  dir.addTask((Task("Eating", "fish", Task::Priority::HIGH, DueTime(DateTime(2019, 01, 01, 23, 0)))));
  dir.addTask(Task("Cooking", "meat", Task::Priority::MEDIUM, DueTime(DateTime(2019,01,01,23,10))));

  dir.addSubtask(1, Task("Drinking", "Cola", Task::Priority::LOW, DueTime(DateTime(2019, 01, 01, 23, 05))));

  dir.showAllTasks();

  return 0;
}
