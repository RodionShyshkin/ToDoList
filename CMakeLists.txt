cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(ToDoList main.cpp src/Task.cpp src/Task.h src/TaskManager.cpp src/TaskManager.h src/DueTime.cpp src/DueTime.h src/FullTask.cpp src/FullTask.h src/taskID.cpp src/taskID.h src/TestTask.cpp src/DueTimeTest.cpp src/taskIDTest.cpp)
target_link_libraries(ToDoList gtest gtest_main)

