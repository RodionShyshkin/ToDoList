cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/MemoryModel/Task.cpp src/MemoryModel/Task.h src/API/TaskService.cpp src/API/TaskService.h src/MemoryModel/Date.cpp
        src/MemoryModel/Date.h src/MemoryModel/TaskEntity.cpp src/MemoryModel/TaskEntity.h src/MemoryModel/IDGenerator.cpp src/MemoryModel/IDGenerator.h
        src/MemoryModel/TaskID.cpp src/MemoryModel/TaskID.h)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS      ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.65.1 REQUIRED COMPONENTS)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

add_executable(Tests tests/MemoryModel/DateTimeTest.cpp tests/MemoryModel/GenerateIDTest.cpp tests/API/TaskServiceTest.cpp
        src/MemoryModel/Date.cpp src/MemoryModel/IDGenerator.cpp src/MemoryModel/TaskID.cpp src/API/TaskService.cpp src/MemoryModel/TaskEntity.cpp src/MemoryModel/Task.cpp src/API/TaskDTO.cpp src/API/TaskDTO.h tests/MemoryModel/TaskEntityTest.cpp src/MemoryModel/TaskStorage.cpp src/MemoryModel/TaskStorage.h src/MemoryModel/TaskView.cpp src/MemoryModel/TaskView.h tests/MemoryModel/TaskViewTest.cpp tests/MemoryModel/TaskTest.cpp tests/MemoryModel/TaskIDTest.cpp tests/MemoryModel/TaskStorageTest.cpp tests/API/TaskDTOTest.cpp src/MemoryModel/TaskServiceStorage.cpp src/MemoryModel/TaskServiceStorage.h tests/MemoryModel/TaskServiceStorageTest.cpp src/MemoryModel/OperationResult.cpp src/MemoryModel/OperationResult.h src/MemoryModel/Error.h tests/MemoryModel/ErrorTest.cpp tests/MemoryModel/OperationResultTest.cpp src/MemoryModel/Priority.h)
#target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

gtest_discover_tests(Tests)

