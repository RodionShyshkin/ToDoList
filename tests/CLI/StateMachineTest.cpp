//
// Created by rodion on 9/19/20.
//

#include <StateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(TaskDTO, getTask, (const TaskID&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, addSubtask, (const TaskID&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult, RemoveTask, (const TaskID&), (override));
  MOCK_METHOD(OperationResult, postponeTask, (const TaskID&, const Date&), (override));
  MOCK_METHOD(OperationResult, completeTask, (const TaskID&), (override));
};

 class StateMachineTest : public ::testing::Test {

};

