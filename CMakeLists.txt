cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(ToDoList main.cpp src/Task.cpp src/Task.h src/TaskManager.cpp src/TaskManager.h src/DateTime.cpp src/DateTime.h src/FullTask.cpp src/FullTask.h src/GenerateID.cpp src/GenerateID.h tests/TestTask.cpp tests/DateTimeTest.cpp tests/taskIDTest.cpp src/DueTime.cpp src/DueTime.h src/TaskID.cpp src/TaskID.h)
target_link_libraries(ToDoList gtest gtest_main)

