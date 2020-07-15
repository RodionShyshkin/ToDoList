#include <iostream>
#include "Task.h"
#include "TaskManager.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  TaskManager dir;

//  dir.addTask(std::make_shared<Task>("Eating", "fish", HIGH, 4));
//  dir.addTask(std::make_shared<Task>("Cooking", "meat", MEDIUM, 6));

  Task first(1, "Eating", "fish", HIGH, 4);
  Task second(2, "Cooking", "meat", MEDIUM, 6);
  Task firstsub(3, "Drinking", "Cola", MEDIUM, 5);
  Task firstSubSub(4, "Trun", "meat", MEDIUM, 5);
  Task third(2, "Zhopa", "Antilopa", LOW, 7);

  dir.addTask(first);
  dir.addTask(second);
  dir.addSubtask(first, firstsub);
  dir.addSubtask(firstsub, firstSubSub);
  dir.addTask(third);

  dir.showTasksForLabel("meat");

  dir.showAllTasks();

  return 0;
}
