cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList main.cpp src/MemoryModel/Task/Task.cpp src/MemoryModel/Task/Task.h src/API/TaskService.cpp src/API/TaskService.h src/MemoryModel/Task/Date.cpp
        src/MemoryModel/Task/Date.h src/MemoryModel/Task/TaskEntity.cpp src/MemoryModel/Task/TaskEntity.h src/MemoryModel/Storage/IDGenerator.cpp src/MemoryModel/Storage/IDGenerator.h
        src/MemoryModel/Task/TaskID.cpp src/MemoryModel/Task/TaskID.h)

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
        src/MemoryModel/Task/Date.cpp src/MemoryModel/Storage/IDGenerator.cpp src/MemoryModel/Task/TaskID.cpp src/API/TaskService.cpp src/MemoryModel/Task/TaskEntity.cpp src/MemoryModel/Task/Task.cpp src/API/TaskDTO.cpp src/API/TaskDTO.h tests/MemoryModel/TaskEntityTest.cpp src/MemoryModel/Storage/TaskStorage.cpp src/MemoryModel/Storage/TaskStorage.h src/MemoryModel/Storage/TaskView.cpp src/MemoryModel/Storage/TaskView.h tests/MemoryModel/TaskViewTest.cpp tests/MemoryModel/TaskTest.cpp tests/MemoryModel/TaskIDTest.cpp tests/MemoryModel/TaskStorageTest.cpp tests/API/TaskDTOTest.cpp src/MemoryModel/Storage/FullStorage.cpp src/MemoryModel/Storage/FullStorage.h tests/MemoryModel/TaskServiceStorageTest.cpp src/MemoryModel/Storage/OperationResult.cpp src/MemoryModel/Storage/OperationResult.h src/MemoryModel/Storage/Error.h tests/MemoryModel/ErrorTest.cpp tests/MemoryModel/OperationResultTest.cpp src/MemoryModel/Task/Priority.h)
#target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

gtest_discover_tests(Tests)

