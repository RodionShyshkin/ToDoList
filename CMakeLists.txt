cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/Task.cpp src/Task.h src/TaskManager.cpp src/TaskManager.h src/DueTime.cpp src/DueTime.h src/TaskID.cpp src/TaskID.h)