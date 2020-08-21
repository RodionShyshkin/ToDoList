cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList src/main.cpp src/core/MemoryModel/Task/Task.cpp src/core/MemoryModel/Task/Task.h src/core/API/TaskService.cpp src/core/API/TaskService.h src/core/MemoryModel/Task/Date.cpp
        src/core/MemoryModel/Task/Date.h src/core/MemoryModel/Task/TaskEntity.cpp src/core/MemoryModel/Task/TaskEntity.h src/core/MemoryModel/Storage/IDGenerator.cpp src/core/MemoryModel/Storage/IDGenerator.h
        src/core/MemoryModel/Task/TaskID.cpp src/core/MemoryModel/Task/TaskID.h)


set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS      ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()
find_package(Boost 1.65.1 REQUIRED COMPONENTS)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(src/core)
include_directories(src/CLI)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

add_executable(Tests tests/core/MemoryModel/Task/DateTest.cpp tests/core/MemoryModel/Storage/GenerateIDTest.cpp tests/core/API/TaskServiceTest.cpp
        src/core/MemoryModel/Task/Date.cpp src/core/MemoryModel/Storage/IDGenerator.cpp src/core/MemoryModel/Task/TaskID.cpp src/core/API/TaskService.cpp src/core/MemoryModel/Task/TaskEntity.cpp src/core/MemoryModel/Task/Task.cpp src/core/API/TaskDTO.cpp src/core/API/TaskDTO.h tests/core/MemoryModel/Task/TaskEntityTest.cpp src/core/MemoryModel/Storage/TaskStorage.cpp src/core/MemoryModel/Storage/TaskStorage.h src/core/MemoryModel/Storage/TaskView.cpp src/core/MemoryModel/Storage/TaskView.h tests/core/MemoryModel/Storage/TaskViewTest.cpp tests/core/MemoryModel/Task/TaskTest.cpp tests/core/MemoryModel/Task/TaskIDTest.cpp tests/core/MemoryModel/Storage/TaskStorageTest.cpp tests/core/API/TaskDTOTest.cpp src/core/MemoryModel/Storage/FullStorage.cpp src/core/MemoryModel/Storage/FullStorage.h tests/core/MemoryModel/Storage/FullStorageTest.cpp src/core/MemoryModel/Storage/OperationResult.cpp src/core/MemoryModel/Storage/OperationResult.h src/core/MemoryModel/Storage/Error.h tests/core/MemoryModel/Storage/OperationResultTest.cpp src/core/MemoryModel/Task/Priority.h src/core/MemoryModel/Storage/TaskViewInterface.h src/core/MemoryModel/Storage/TaskStorageInterface.h src/core/MemoryModel/Storage/FullStorageInterface.h src/core/MemoryModel/Storage/IDGeneratorInterface.h src/CLI/States/StateInterface.h tests/CLI/base.cpp src/CLI/States/StartState.cpp src/CLI/States/StartState.h src/CLI/StateStorage.cpp src/CLI/StateStorage.h src/CLI/States/ExitState.cpp src/CLI/States/ExitState.h src/CLI/CommandParser.cpp src/CLI/CommandParser.h src/CLI/States/AddTaskState.cpp src/CLI/States/AddTaskState.h src/CLI/States/ViewTaskState.cpp src/CLI/States/ViewTaskState.h src/CLI/Operation.h src/CLI/States/TaskState.cpp src/CLI/States/TaskState.h src/CLI/States/RemoveTaskState.cpp src/CLI/States/RemoveTaskState.h src/CLI/States/TaskListState.cpp src/CLI/States/TaskListState.h)

target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

gtest_discover_tests(Tests)

