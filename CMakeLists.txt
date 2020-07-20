cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/Task.cpp src/Task.h src/TaskManager.cpp src/TaskManager.h src/DateTime.cpp
    src/DateTime.h src/FullTask.cpp src/FullTask.h src/GenerateID.cpp src/GenerateID.h
        src/DueTime.cpp src/DueTime.h src/TaskID.cpp src/TaskID.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

add_executable(Tests tests/DateTimeTest.cpp tests/DueTimeTest.cpp tests/GenerateIDTest.cpp tests/TaskManagerTest.cpp tests/TestTask.cpp
        src/DateTime.cpp src/DueTime.cpp src/GenerateID.cpp src/TaskID.cpp src/TaskManager.cpp src/FullTask.cpp src/Task.cpp)
target_link_libraries(Tests gtest gtest_main)

