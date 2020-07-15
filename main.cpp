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
  Task firstSubSub("Trun", "Huyun", MEDIUM, 5);
  dir.addTask(first);
  dir.addTask(second);

  auto ptr = std::make_shared<Task>(first);
  dir.addSubtask(ptr, firstsub);

  auto ptr2 = std::make_shared<Task>(firstsub);
  dir.addSubtask(ptr2, firstSubSub);

  dir.showAllTasks();

  return 0;
}
