#include <iostream>
#include "src/Task.h"
#include "src/TaskManager.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  TaskManager dir;

//  dir.addTask(std::make_shared<Task>("Eating", "fish", HIGH, 4));
//  dir.addTask(std::make_shared<Task>("Cooking", "meat", MEDIUM, 6));

  Task first("Eating", "fish", HIGH, DueTime(2019, 01, 01, 23, 0, 0));
  Task second("Cooking", "meat", MEDIUM, DueTime(2019, 01, 01, 23, 10, 0));
  Task firstsub("Drinking", "Cola", MEDIUM, DueTime(2019, 01, 01, 23, 20, 0));
  Task firstSubSub("Trun", "meat", MEDIUM, DueTime(2020, 16, 07, 04, 18, 2));
  Task third("Zhopa", "Antilopa", LOW, DueTime(2020, 16, 07, 04, 21, 23));

  dir.addTask(first);
  dir.addTask(second);
  dir.addSubtask(1, firstsub);
  dir.addSubtask(3, firstSubSub);

  dir.addSubtask(4, third);
  dir.addTask(third);

  dir.showTasksForLabel("meat");

  std::cout << std::endl << std::endl;

  dir.markTask(4);
  dir.showAllTasks();

  return 0;
}
