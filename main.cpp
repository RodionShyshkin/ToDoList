#include <iostream>
#include "MemoryModel/Task/Task.h"
#include "src/API/TaskService.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  TaskService dir;

  dir.addTask(Task("Eating", "dinner", Task::Priority::HIGH, Date(2020, 07, 19, 16, 0)));
  dir.addTask(Task("Write code", "C++", Task::Priority::MEDIUM, Date(2020, 07, 21, 23, 0)));
  dir.addSubtask(1, Task("Drink", "dinner", Task::Priority::LOW, Date(2020, 07, 19, 16, 05)));
  return 0;
}
