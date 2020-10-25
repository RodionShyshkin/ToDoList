//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKMODEL_H_
#define TODOLIST_TESTS_MOCKS_MOCKMODEL_H_

#include <gmock/gmock.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

class MockModel : public TaskModelInterface {
 public:
  MOCK_METHOD(std::optional<ModelTaskDTO>, getTask, (const TaskID&), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getAllTasks, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForToday, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForWeek, (), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksByLabel, (const std::string &label), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksByName, (const std::string& name), (const, override));
  MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksByPriority, (const Priority& priority), (const, override));

  MOCK_METHOD(bool, postponeTask, (const TaskID& id, const Date& newdate), (override));
  MOCK_METHOD(bool, completeTask, (const TaskID& id), (override));

  MOCK_METHOD(OperationResult<StorageError>, AddTask, (const ModelTaskDTO& task), (override));
  MOCK_METHOD(OperationResult<StorageError>, AddSubtask, (const TaskID &id, const ModelTaskDTO& subtask), (override));
  MOCK_METHOD(OperationResult<StorageError>, RemoveTask, (const TaskID& id), (override));

  MOCK_METHOD(std::vector<ModelTaskDTO>, GetSubtasks, (const TaskID& id), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKMODEL_H_
