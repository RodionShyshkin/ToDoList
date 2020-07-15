#include <iostream>
#include "Task.h"
#include "TaskManager.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  TaskManager dir;

//  dir.addTask(std::make_shared<Task>("Eating", "fish", HIGH, 4));
//  dir.addTask(std::make_shared<Task>("Cooking", "meat", MEDIUM, 6));

  Task first("Eating", "fish", HIGH, 4);
  Task second("Cooking", "meat", MEDIUM, 6);
  Task firstsub("Drinking", "Cola", MEDIUM, 5);
  Task firstSubSub("Trun", "meat", MEDIUM, 5);

  dir.addTask(first);
  dir.addTask(second);
  dir.addSubtask(first, firstsub);
  dir.addSubtask(firstsub, firstSubSub);

  dir.showTasksForLabel("meat");

  dir.showAllTasks();

  return 0;
}
