cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/MemoryModel/Task.cpp src/MemoryModel/Task.h src/API/TaskService.cpp src/API/TaskService.h src/MemoryModel/DateTime.cpp
        src/MemoryModel/DateTime.h src/MemoryModel/FullTask.cpp src/MemoryModel/FullTask.h src/MemoryModel/GenerateID.cpp src/MemoryModel/GenerateID.h
        src/MemoryModel/DueTime.cpp src/MemoryModel/DueTime.h src/MemoryModel/TaskID.cpp src/MemoryModel/TaskID.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(src/MemoryModel)
include_directories(src/API)

add_executable(Tests tests/DateTimeTest.cpp tests/GenerateIDTest.cpp tests/TaskServiceTest.cpp
        src/MemoryModel/DateTime.cpp src/MemoryModel/DueTime.cpp src/MemoryModel/GenerateID.cpp src/MemoryModel/TaskID.cpp src/API/TaskService.cpp src/MemoryModel/FullTask.cpp src/MemoryModel/Task.cpp src/API/TaskOutput.cpp src/API/TaskOutput.h src/MemoryModel/FullTaskDTO.cpp src/MemoryModel/FullTaskDTO.h tests/FullTaskTest.cpp)
target_link_libraries(Tests gtest gtest_main)

