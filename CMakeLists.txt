cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/MemoryModel/Task.cpp src/MemoryModel/Task.h src/API/TaskService.cpp src/API/TaskService.h src/MemoryModel/DateTime.cpp
        src/MemoryModel/DateTime.h src/MemoryModel/TaskEntity.cpp src/MemoryModel/TaskEntity.h src/MemoryModel/GenerateID.cpp src/MemoryModel/GenerateID.h
        src/MemoryModel/DueTime.cpp src/MemoryModel/DueTime.h src/MemoryModel/TaskID.cpp src/MemoryModel/TaskID.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(src/MemoryModel)
include_directories(src/API)
include_directories(tests)

set(BOOST_ROOT "/usr/include/boost/version.hpp")
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

add_executable(Tests tests/DateTimeTest.cpp tests/GenerateIDTest.cpp tests/TaskServiceTest.cpp
        src/MemoryModel/DateTime.cpp src/MemoryModel/DueTime.cpp src/MemoryModel/GenerateID.cpp src/MemoryModel/TaskID.cpp src/API/TaskService.cpp src/MemoryModel/TaskEntity.cpp src/MemoryModel/Task.cpp src/API/TaskDTO.cpp src/API/TaskDTO.h tests/TaskEntityTest.cpp src/MemoryModel/TaskOwner.cpp src/MemoryModel/TaskOwner.h src/API/TaskView.cpp src/API/TaskView.h)
target_link_libraries(Tests gtest gtest_main)

