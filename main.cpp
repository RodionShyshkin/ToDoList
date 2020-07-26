#include <iostream>
#include "src/MemoryModel/Task.h"
#include "src/API/TaskManager.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  TaskManager dir;

  dir.addTask(Task("Eating", "dinner", Task::Priority::HIGH, DateTime(2020, 07, 19, 16, 0)));
  dir.addTask(Task("Write code", "C++", Task::Priority::MEDIUM, DateTime(2020, 07, 21, 23, 0)));
  dir.addSubtask(1, Task("Drink", "dinner", Task::Priority::LOW, DateTime(2020, 07, 19, 16, 05)));
  return 0;
}
