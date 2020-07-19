set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(ToDoList main.cpp src/Task.cpp src/Task.h src/TaskManager.cpp src/TaskManager.h src/DateTime.cpp src/DateTime.h src/FullTask.cpp src/FullTask.h src/GenerateID.cpp src/GenerateID.h tests/TestTask.cpp tests/DateTimeTest.cpp src/DueTime.cpp src/DueTime.h src/TaskID.cpp src/TaskID.h tests/DueTimeTest.cpp tests/GenerateIDTest.cpp tests/TaskManagerTest.cpp)
target_link_libraries(ToDoList gtest gtest_main)

