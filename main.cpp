#include <iostream>
#include "Task.h"

int main() {
  std::cout << "Hello, World!" << std::endl;
  Task kek("Eating", "fish", HIGH, 4);

  std::cout << kek.getDate() << std::endl << kek.getName() << " " << kek.getLabel() << std::endl << kek.getPriority() << std::endl;

  return 0;
}
