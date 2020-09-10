//
// Created by rodion on 9/10/20.
//

#include <iostream>
#include "ConsoleIO.h"

std::string ConsoleIO::input() const {
  std::string stringInput;
  std::getline(std::cin, stringInput);
  return stringInput;
}

void ConsoleIO::output(const std::string &string) const {
  std::cout << "[O]: " << string << std::endl;
}
