//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_
#define TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_

#include <gmock/gmock.h>
#include <API/TaskServiceInterface.h>

class MockService : public TaskServiceInterface {
 public:
  MOCK_METHOD(std::optional<TaskDTO>, GetTask, (const unsigned int&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetAllTasks, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksForToday, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksForWeek, (const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByLabel, (const std::string &, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByName, (const std::string&, const bool&), (const, override));
  MOCK_METHOD(std::vector<TaskDTO>, GetTasksByPriority, (const Priority&), (const, override));

  MOCK_METHOD(OperationResult<StorageError>, AddTask, (const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, AddSubtask, (const unsigned int&, const TaskDTO&), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const unsigned int&), (override));
  MOCK_METHOD(bool, PostponeTask, (const unsigned int&, const boost::gregorian::date&), (override));
  MOCK_METHOD(bool, CompleteTask, (const unsigned int&), (override));

  MOCK_METHOD(OperationResult<PersistError>, Save, (const std::string&), (override));
  MOCK_METHOD(OperationResult<PersistError>, Load, (const std::string&), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKSERVICE_H_
