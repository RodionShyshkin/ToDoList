cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

######## CORE ########

file(GLOB core_sources "src/core/API/*.cpp" "src/core/MemoryModel/Storage/*.cpp" "src/core/MemoryModel/Task/*.cpp")
file(GLOB core_headers "src/core/API/*.h" "src/core/MemoryModel/Storage/*.h" "src/core/MemoryModel/Task/*.h")

######## CLI ########

file(GLOB cli_sources "src/CLI/*.cpp" "src/CLI/States/*.cpp" "src/CLI/States/AddingTask/*.cpp"
        "src/CLI/States/GetTasksList/*.cpp" "src/CLI/States/GetSingleTask/*.cpp"
        "src/CLI/States/EditStates/*.cpp" "src/CLI/States/EditStates/Postpone/*.cpp" "src/CLI/States/MainStates/*.cpp"
        "src/CLI/Context/*.cpp" "src/CLI/IO/*.cpp")
file(GLOB cli_headers "src/CLI/*.h" "src/CLI/States/*.h" "src/CLI/States/AddingTask/*.h"
        "src/CLI/States/GetTasksList/*.h" "src/CLI/States/GetSingleTask/*.h"
        "src/CLI/States/EditStates/*.h" "src/CLI/States/EditStates/Postpone/*.h" "src/CLI/States/MainStates/*.h"
        "src/CLI/Context/*.h" "src/CLI/IO/*.h")

file(GLOB main "src/main.cpp")

add_executable(ToDoList ${core_sources} ${core_headers} ${cli_sources} ${cli_headers} ${main})

######## TESTS ########
file(GLOB core_tests "tests/core/API/*.cpp" "tests/core/MemoryModel/Storage/*.cpp" "tests/core/MemoryModel/Task/*.cpp")

file(GLOB cli_tests "tests/CLI/*.cpp")

######## BOOST ########

set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS      ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.65.1 COMPONENTS date_time REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

######## GTEST ########

include_directories(src/core)
include_directories(src/CLI)
include_directories(tests)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

add_executable(Tests ${core_tests} ${core_sources} ${cli_sources} ${cli_tests})

set(GMOCK_L "/usr/local/lib/gmock/")
target_link_libraries(Tests GTest::GTest GTest::Main)
target_link_libraries(Tests ${Boost_LIBRARIES})

target_link_libraries(ToDoList ${Boost_LIBRARIES})

gtest_discover_tests(Tests)


