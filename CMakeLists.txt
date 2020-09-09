cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

file(GLOB core_sources "src/core/API/*.cpp" "src/core/MemoryModel/Storage/*.cpp" "src/core/MemoryModel/Task/*.cpp")
file(GLOB core_headers "src/core/API/*.h" "src/core/MemoryModel/Storage/*.h" "src/core/MemoryModel/Task/*.h")

file(GLOB cli_sources "src/CLI/*.cpp" "src/CLI/States/*.cpp" "src/CLI/States/AddingTask/*.cpp"
        "src/CLI/States/ShowTasksList/*.cpp" "src/CLI/States/GetSingleTask/*.cpp")
file(GLOB cli_headers "src/CLI/*.h" "src/CLI/States/*.h" "src/CLI/States/AddingTask/*.h"
        "src/CLI/States/ShowTasksList/*.h" "src/CLI/States/GetSingleTask/*.h")

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

add_executable(Tests ${core_tests} ${core_sources} ${cli_sources} src/CLI/States/NewDateParamState.cpp src/CLI/States/NewDateParamState.h src/core/API/TaskServiceInterface.h src/CLI/Context/BufferInterface.h src/CLI/Context/IDBuffer.cpp src/CLI/Context/IDBuffer.h src/CLI/Context/AddTaskBuffer.cpp src/CLI/Context/AddTaskBuffer.h src/CLI/Context/ShowListBuffer.cpp src/CLI/Context/ShowListBuffer.h src/CLI/Context/PostponeBuffer.cpp src/CLI/Context/PostponeBuffer.h src/CLI/AvailableCommands.cpp src/CLI/AvailableCommands.h)

target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

gtest_discover_tests(Tests)


