//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <API/TaskService.h>
#include <Persister/PersisterInterface.h>
#include <Mocks/MockModel.h>

using ::testing::Return;

class TaskServiceTest : public ::testing::Test {
 public:

  void SetUp() override {
    task1 = TaskDTO::create(1, "Task", "label",
                                    Priority::EMPTY, boost::gregorian::date{2040-9-20}, false);
    task2 = TaskDTO::create(2, "Task 2", "label",
                                    Priority::MEDIUM, boost::gregorian::date{2019-4-12}, false);
    task3 = TaskDTO::create(3, "Task 3", "label",
                                          Priority::HIGH, Date::GetCurrentDate().GetDate(), true);
    task4 = TaskDTO::create(4, "Task 4", "label",
                                          Priority::LOW, Date::GetCurrentDate().GetDate(), false);

    task1_dto = ModelTaskDTO::createWithoutParent(TaskID{task1.getID()}, task1.getName(), task1.getLabel(),
                                                  task1.getPriority(), Date{task1.getDueDate()}, task1.getStatus());

    task2_dto = ModelTaskDTO::createWithoutParent(TaskID{task2.getID()}, task2.getName(), task2.getLabel(),
                                                  task2.getPriority(), Date{task2.getDueDate()}, task2.getStatus());

    task3_dto = ModelTaskDTO::createWithoutParent(TaskID{task3.getID()}, task3.getName(), task3.getLabel(),
                                                  task3.getPriority(), Date{task3.getDueDate()}, task3.getStatus());

    task4_dto = ModelTaskDTO::createWithoutParent(TaskID{task4.getID()}, task4.getName(), task4.getLabel(),
                                                  task4.getPriority(), Date{task4.getDueDate()}, task4.getStatus());
  }

  void TearDown() override {

  }

  TaskDTO task1;
  TaskDTO task2;
  TaskDTO task3;
  TaskDTO task4;

  ModelTaskDTO task1_dto;
  ModelTaskDTO task2_dto;
  ModelTaskDTO task3_dto;
  ModelTaskDTO task4_dto;
};

TEST_F(TaskServiceTest, shouldAddTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));

  TaskService service{std::move(model)};

  auto result = service.addTask(task1);
  ASSERT_EQ(result.GetError(), std::nullopt);
}

TEST_F(TaskServiceTest, shouldAddSubtaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddSubtask).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));

  TaskService service{std::move(model)};

  auto result = service.addSubtask(1, task1);
  ASSERT_EQ(result.GetError(), std::nullopt);
}

TEST_F(TaskServiceTest, shouldRemoveTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, RemoveTask).Times(1).WillOnce(Return(OperationResult<StorageError>::Success()));

  TaskService service{std::move(model)};

  auto result = service.RemoveTask(1);
  ASSERT_EQ(result.GetError(), std::nullopt);
}

TEST_F(TaskServiceTest, shouldCompleteTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, completeTask).Times(1).WillOnce(Return(true));

  TaskService service{std::move(model)};

  auto result = service.completeTask(1);
  ASSERT_TRUE(result);
}

TEST_F(TaskServiceTest, shouldPostponeTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, postponeTask).Times(1).WillOnce(Return(true));

  TaskService service{std::move(model)};

  auto result = service.postponeTask(1, boost::gregorian::date{2020-1-30});
  ASSERT_TRUE(result);
}

TEST_F(TaskServiceTest, shouldGetAllTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getAllTasks).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getAllTasks(true);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task1.getID());
  ASSERT_EQ(result[1].getID(), task4.getID());
  ASSERT_EQ(result[2].getID(), task2.getID());
  ASSERT_EQ(result[3].getID(), task3.getID());
}

TEST_F(TaskServiceTest, shouldGetTodayTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getTasksForToday).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getTasksForToday(true);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task1.getID());
  ASSERT_EQ(result[1].getID(), task4.getID());
  ASSERT_EQ(result[2].getID(), task2.getID());
  ASSERT_EQ(result[3].getID(), task3.getID());
}

TEST_F(TaskServiceTest, shouldGetWeekTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getTasksForWeek).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getTasksForWeek(true);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task1.getID());
  ASSERT_EQ(result[1].getID(), task4.getID());
  ASSERT_EQ(result[2].getID(), task2.getID());
  ASSERT_EQ(result[3].getID(), task3.getID());
}

TEST_F(TaskServiceTest, shouldGetLabelTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getTasksByLabel).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getTasksByLabel("label", true);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task1.getID());
  ASSERT_EQ(result[1].getID(), task4.getID());
  ASSERT_EQ(result[2].getID(), task2.getID());
  ASSERT_EQ(result[3].getID(), task3.getID());
}

TEST_F(TaskServiceTest, shouldGetNameTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getTasksByName).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getTasksByName("name", true);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task1.getID());
  ASSERT_EQ(result[1].getID(), task4.getID());
  ASSERT_EQ(result[2].getID(), task2.getID());
  ASSERT_EQ(result[3].getID(), task3.getID());
}

TEST_F(TaskServiceTest, shouldGetPriorityTasksWithSortingCorrectly) {
  auto model = std::make_unique<MockModel>();
  std::vector<ModelTaskDTO> model_dto_tasks;
  model_dto_tasks.push_back(task3_dto);
  model_dto_tasks.push_back(task2_dto);
  model_dto_tasks.push_back(task4_dto);
  model_dto_tasks.push_back(task1_dto);

  EXPECT_CALL(*model, getTasksByPriority).Times(1).WillOnce(Return(model_dto_tasks));

  TaskService service{std::move(model)};

  auto result = service.getTasksByPriority(Priority::MEDIUM);

  ASSERT_EQ(result.size(), 4);
  ASSERT_EQ(result[0].getID(), task3.getID());
  ASSERT_EQ(result[1].getID(), task2.getID());
  ASSERT_EQ(result[2].getID(), task4.getID());
  ASSERT_EQ(result[3].getID(), task1.getID());
}

TEST_F(TaskServiceTest, shouldPersistTasksCorrectly) {
  TaskService service;
  service.addTask(task1);
  service.addSubtask(task1.getID(), task2);
  service.addTask(task3);

  service.Save("testservice.txt");

  TaskService service_load;
  service_load.Load("testservice.txt");

  auto before = service.getAllTasks(false);
  auto after = service_load.getAllTasks(false);

  ASSERT_EQ(before.size(), after.size());
}

TEST_F(TaskServiceTest, shouldGetTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, getTask).Times(1).WillOnce(Return(task1_dto));

  TaskService service{std::move(model)};

  auto result = service.getTask(1);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.value().getID(), TaskID{1});
}

TEST_F(TaskServiceTest, shouldNotGetTaskWhichDoesNotExist) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, getTask).Times(1).WillOnce(Return(std::nullopt));

  TaskService service{std::move(model)};

  auto result = service.getTask(1);

  ASSERT_FALSE(result.has_value());
}
