//
// Created by rodion on 9/10/20.
//

#include <iostream>
#include "ConsoleIO.h"

std::string ConsoleIO::input() {
  std::string stringInput;
  std::getline(std::cin, stringInput);
  return stringInput;
}

std::string ConsoleIO::inputCommand() {
  std::cout << ">> ";
  return this->input();
}

void ConsoleIO::output(const std::string &string) {
  std::cout << string;
}

void ConsoleIO::outputWithBreak(const std::string &string) {
  this->output(string);
  std::cout << std::endl;
}