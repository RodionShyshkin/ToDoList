#include <iostream>
#include "src/Task.h"
#include "src/TaskManager.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  TaskManager dir;

  dir.addTask(Task("Eating", "dinner", Task::Priority::HIGH, DueTime(DateTime(2020, 07, 19, 16, 0))));
  dir.addTask(Task("Write code", "C++", Task::Priority::MEDIUM, DueTime(DateTime(2020, 07, 21, 23, 0))));
  dir.addSubtask(1, Task("Drink", "dinner", Task::Priority::LOW, DueTime(DateTime(2020, 07, 19, 16, 05))));

//  dir.removeTask(2);

  dir.showTasksForToday();

//  dir.showAllTasks();
//  dir.showTasksForLabel("dinner");



/*
  TaskManager dir;

  dir.addTask((Task("Eating", "fish", Task::Priority::HIGH, DueTime(DateTime(2019, 01, 01, 23, 0)))));
  dir.addTask(Task("Cooking", "meat", Task::Priority::MEDIUM, DueTime(DateTime(2019,01,01,23,10))));

  dir.addSubtask(1, Task("Drinking", "Cola", Task::Priority::LOW, DueTime(DateTime(2019, 01, 01, 23, 05))));

  dir.showAllTasks();

  dir.addTask(Task("Take pizza", "Margaret", Task::Priority::HIGH, DueTime(DateTime(2020, 07, 18, 16, 15))));
  dir.postponeTask(4, DateTime(2020, 07, 18, 16, 20));

  std::cout << "---" << std::endl;
  dir.showTasksForToday();
  std::cout << "++++++ " << std::endl << std::endl;
  dir.removeTask(1);
  dir.showAllTasks();

  DateTime lhs(2020, 07, 14, 10, 59);

  const std::type_info& t1 = typeid(lhs);
  std::cout << t1.name() << std::endl;*/
  return 0;
}
