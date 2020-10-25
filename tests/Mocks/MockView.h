//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_TESTS_MOCKS_MOCKVIEW_H_
#define TODOLIST_TESTS_MOCKS_MOCKVIEW_H_

#include <gmock/gmock.h>
#include <MemoryModel/Storage/TaskViewInterface.h>

class MockView : public TaskViewInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::weak_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetTodayTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetWeekTasks, (), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetAllTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByLabel, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByName, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByPriority, (const Priority&), (override));
};

#endif //TODOLIST_TESTS_MOCKS_MOCKVIEW_H_
