//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_
#define TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_

#include <gmock/gmock.h>
#include <API/TaskServiceInterface.h>

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(std::optional<TaskDTO>, getTask, (const unsigned int&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, getTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult<StorageError>, addTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, addSubtask, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(bool, postponeTask, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(bool, completeTask, (const unsigned int&), (override));

  MOCK_METHOD(OperationResult<PersistError>, Save, (const std::string&), (override));
  MOCK_METHOD(OperationResult<PersistError>, Load, (const std::string&), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_
