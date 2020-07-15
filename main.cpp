#include <iostream>
#include "Task.h"
#include "TaskManager.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  TaskManager dir;

  dir.addTask(std::make_shared<Task>("Eating", "fish", HIGH, 4));
  dir.addTask(std::make_shared<Task>("Cooking", "meat", MEDIUM, 6));
  dir.showAllTasks();

  return 0;
}
