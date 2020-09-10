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

std::string ConsoleIO::inputCommand() const {
  std::cout << ">> ";
  return this->input();
}

void ConsoleIO::output(const std::string &string) const {
  std::cout << string;
}

void ConsoleIO::outputWithBreak(const std::string &string) const {
  this->output(string);
  std::cout << std::endl;
}