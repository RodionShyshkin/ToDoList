//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKMODEL_H_
#define TODOLIST_TESTS_MOCKS_MOCKMODEL_H_

#include <gmock/gmock.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

class MockModel : public TaskModelInterface {
 public:
  MOCK_METHOD(std::optional<ModelTaskDTO>, GetTask, (const TaskID&), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetAllTasks, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetTasksForToday, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetTasksForWeek, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetTasksByLabel, (const std::string &label), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetTasksByName, (const std::string& name), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, GetTasksByPriority, (const Priority& priority), (const, override));

  MOCK_METHOD(bool, PostponeTask, (const TaskID& id, const Date& newdate), (override));
  MOCK_METHOD(bool, CompleteTask, (const TaskID& id), (override));

  MOCK_METHOD(OperationResult<StorageError>, AddTask, (const ModelTaskDTO& task), (override));
  MOCK_METHOD(OperationResult<StorageError>, AddSubtask, (const TaskID &id, const ModelTaskDTO& subtask), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const TaskID& id), (override));

  MOCK_METHOD(std::vector<ModelTaskDTO>, GetSubtasks, (const TaskID& id), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKMODEL_H_
