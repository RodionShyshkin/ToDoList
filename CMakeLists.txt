cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

file(GLOB core_sources "src/core/API/*.cpp" "src/core/MemoryModel/Storage/*.cpp" "src/core/MemoryModel/Task/*.cpp")
file(GLOB core_headers "src/core/API/*.h" "src/core/MemoryModel/Storage/*.h" "src/core/MemoryModel/Task/*.h")

file(GLOB cli_sources "src/CLI/*.cpp" "src/CLI/States/*.cpp")
file(GLOB cli_headers "src/CLI/*.h" "src/CLI/States/*.h")

file(GLOB main "src/main.cpp")

add_executable(ToDoList ${core_sources} ${core_headers} ${cli_sources} ${cli_headers} ${main})


set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS      ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)


include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()


find_package(Boost 1.65.1 COMPONENTS date_time REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


include_directories(src/core)
include_directories(src/CLI)
include_directories(tests)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

file(GLOB core_tests "tests/core/API/*.cpp" "tests/core/MemoryModel/Storage/*.cpp" "tests/core/MemoryModel/Task/*.cpp"
        "tests/CLI/base.cpp")

add_executable(Tests ${core_tests} ${core_sources} ${cli_sources} src/CLI/Context.cpp src/CLI/Context.h src/CLI/States/StateFactory.cpp src/CLI/States/StateFactory.h src/CLI/States/AddingTask/AddTaskStartState.cpp src/CLI/States/AddingTask/AddTaskStartState.h src/CLI/States/AddingTask/NameParamState.cpp src/CLI/States/AddingTask/NameParamState.h src/CLI/States/AddingTask/AddTaskStateMachine.cpp src/CLI/States/AddingTask/AddTaskStateMachine.h src/CLI/States/AddingTask/AddTaskStateInterface.h src/CLI/States/AddingTask/LabelParamState.cpp src/CLI/States/AddingTask/LabelParamState.h src/CLI/States/AddingTask/PriorityParamState.cpp src/CLI/States/AddingTask/PriorityParamState.h src/CLI/States/AddingTask/DateParamState.cpp src/CLI/States/AddingTask/DateParamState.h src/CLI/States/AddingTask/AddTaskExitState.cpp src/CLI/States/AddingTask/AddTaskExitState.h src/CLI/States/AddingTask/AddTaskContext.cpp src/CLI/States/AddingTask/AddTaskContext.h src/CLI/ContextInterface.h src/CLI/States/ShowTasksLIst/ShowListStateMachine.cpp src/CLI/States/ShowTasksLIst/ShowListStateMachine.h src/CLI/States/ShowTasksLIst/ShowListContext.cpp src/CLI/States/ShowTasksLIst/ShowListContext.h src/CLI/States/ShowTasksLIst/ShowListStateInterface.h src/CLI/States/ShowTasksLIst/ShowListStartState.cpp src/CLI/States/ShowTasksLIst/ShowListStartState.h src/CLI/States/ShowTasksLIst/ShowListExitState.cpp src/CLI/States/ShowTasksLIst/ShowListExitState.h src/CLI/States/ShowTasksLIst/ModifierParamState.cpp src/CLI/States/ShowTasksLIst/ModifierParamState.h src/CLI/States/ShowTasksLIst/SortedParamState.cpp src/CLI/States/ShowTasksLIst/SortedParamState.h)

target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

gtest_discover_tests(Tests)

