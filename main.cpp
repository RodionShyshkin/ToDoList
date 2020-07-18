#include <iostream>
#include "src/Task.h"
#include "src/TaskManager.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  TaskManager dir;

  dir.addTask((Task("Eating", "fish", Task::Priority::HIGH, DueTime(DateTime(2019, 01, 01, 23, 0)))));
  dir.addTask(Task("Cooking", "meat", Task::Priority::MEDIUM, DueTime(DateTime(2019,01,01,23,10))));

  dir.addSubtask(1, Task("Drinking", "Cola", Task::Priority::LOW, DueTime(DateTime(2019, 01, 01, 23, 05))));
//  dir.addSubtask(1, Task("Whiskey", "cola", Task::Priority::LOW, DueTime(DateTime(2019, 01, 01, 25, 1))));

  dir.showAllTasks();

  dir.addTask(Task("Take pizza", "Margaret", Task::Priority::HIGH, DueTime(DateTime(2020, 07, 18, 16, 15))));
  dir.postponeTask(4, DateTime(2020, 07, 18, 16, 20));

  std::cout << "---" << std::endl;
  dir.showTasksForToday();

  return 0;
}
