//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <API/TaskService.h>

class TaskServiceTest : public ::testing::Test {
 public:

  void SetUp() override {
    std::optional<Task> task = Task::create("Task", "label", Priority::EMPTY, Date(2040, 9, 20));
    std::optional<Task> task2 = Task::create("Task", "label", Priority::MEDIUM, Date(2019, 4, 12));
    std::optional<Task> task3 = Task::create("Task 2", "label", Priority::HIGH, Date::GetCurrentDate());
    std::optional<Task> task4 = Task::create("Task 2", "label", Priority::LOW, Date::GetCurrentDate());

    service.addTask(TaskDTO::create(TaskID{1}, task.value(), false));
    service.addTask(TaskDTO::create(TaskID{2}, task2.value(), true));
    service.addSubtask(TaskID{1}, TaskDTO::create(TaskID{3}, task3.value(), true));
    service.addSubtask(TaskID{3}, TaskDTO::create(TaskID{4}, task4.value(), false));
  }

  void TearDown() override {

  }

  TaskService service;
};

/*class MockView : public TaskViewInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::weak_ptr<TaskEntity>&), (override));

};
*/
/*
TEST_F(TaskServiceTest, getAlltasks) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getAllTasks(true));

  ASSERT_EQ(tasks.size(), 4);
  ASSERT_EQ(tasks[0].getPriority(), Priority::EMPTY);
  ASSERT_EQ(tasks[1].getPriority(), Priority::LOW);
  ASSERT_EQ(tasks[2].getPriority(), Priority::MEDIUM);
  ASSERT_EQ(tasks[3].getPriority(), Priority::HIGH);

}

TEST_F(TaskServiceTest, getallEmptyVector) {
  TaskService empty;
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = empty.getAllTasks(true));
  ASSERT_TRUE(tasks.empty());
}

TEST_F(TaskServiceTest, getTodayTasksNoSorted) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksForToday(false));

  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::HIGH);
  ASSERT_EQ(tasks[1].getPriority(), Priority::LOW);
}

TEST_F(TaskServiceTest, getTodayTasksSorted) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksForToday(true));

  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::LOW);
  ASSERT_EQ(tasks[1].getPriority(), Priority::HIGH);
}

TEST_F(TaskServiceTest, getTodayEmptyVector) {
  TaskService empty;
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = empty.getTasksForToday(true));
  ASSERT_TRUE(tasks.empty());
}

TEST_F(TaskServiceTest, getWeekTasks) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksForWeek(false));

  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::HIGH);
  ASSERT_EQ(tasks[1].getPriority(), Priority::LOW);
}

TEST_F(TaskServiceTest, getWeekTasksSorted) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksForWeek(true));

  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::LOW);
  ASSERT_EQ(tasks[1].getPriority(), Priority::HIGH);
}

TEST_F(TaskServiceTest, getWeekEmptyVector) {
  TaskService empty;
  std::vector<TaskDTO> tasks;

  EXPECT_NO_THROW(tasks = empty.getTasksForWeek(false));
  ASSERT_TRUE(tasks.empty());
  EXPECT_NO_THROW(tasks = empty.getTasksForWeek(true));
  ASSERT_TRUE(tasks.empty());
}
*/
TEST_F(TaskServiceTest, remove) {
  /*service.addTask(task);
  service.addSubtask(1, subtask);
  service.addSubtask(1, task);
  service.addTask(subtask);
  auto tasks = service.getDebug();*/
  //std::cout << tasks[0].GetSubtasks().size();

//  std::cout << std::endl << std::endl << tasks[0].GetID().GetID() << tasks[1].GetID().GetID() << tasks[2].GetID().GetID()
//  << tasks[3].GetID().GetID() << std::endl;

//  std::cout << tasks.size() << std::endl;
/*  service.RemoveTask(4);
  tasks = service.getDebug();
  auto item = service.getDebug2();*/
  //std::cout << item.GetTask(4)->GetID().GetID();
//  std::cout << item.HasTask(4);
//  std::cout << tasks.size() << std::endl;

}

TEST_F(TaskServiceTest, RemoveTaskWithSubtasks) {
/*  EXPECT_NO_THROW(service.RemoveTask(TaskID::create(1).value()));

  auto tasks = service.getAllTasks(false);

  ASSERT_EQ(tasks.size(), 1);*/



/*  service.addTask(task);
  service.addSubtask(1, subtask);
  service.addSubtask(1, task);
  service.addTask(subtask);
  auto tasks = service.getDebug();

  std::cout << std::endl << std::endl << tasks[0].GetID().GetID() << tasks[1].GetID().GetID() << tasks[2].GetID().GetID()
  << tasks[3].GetID().GetID() << std::endl;

  std::cout << tasks.size() << std::endl;

  service.RemoveFullTask(1);
  tasks = service.getDebug();
  auto item = service.getDebug2();

  std::cout << tasks.size();

  std::cout << tasks[0].GetID().GetID();*/
}


//TEST_F(TaskServiceTest, postpone) {
/*  service.addTask(task);
  service.addSubtask(TaskID::create(1).value(), subtask);
  service.addSubtask(TaskID::create(1).value(), task);
  service.addTask(subtask);

  auto tasks = service.getDebug();
  auto item = service.getDebug2();
  std::cout << tasks[0].GetStatus() << std::endl;

  auto k = item.GetTask(TaskID::create(1).value());
  std::cout << k->GetStatus() << std::endl;

  service.completeTask(TaskID::create(1).value());

  tasks = service.getDebug();
  k = item.GetTask(TaskID::create(1).value());

  std::cout << k->GetStatus() << std::endl;
  std::cout << tasks[0].GetStatus() << std::endl;*/
/*}


TEST_F(TaskServiceTest, addTask) {*/
/*  service.addTask(task);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 1);*/
/*}

TEST_F(TaskServiceTest, addSubtask) {*/
/*  service.addTask(task);
  service.addSubtask(1, subtask);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 2);*/
/*}

TEST_F(TaskServiceTest, getTaskByName) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksByName("Task", false));

  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::EMPTY);
  ASSERT_EQ(tasks[1].getPriority(), Priority::MEDIUM);

  EXPECT_NO_THROW(tasks = service.getTasksByName("Task 2", true));
  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].getPriority(), Priority::LOW);
  ASSERT_EQ(tasks[1].getPriority(), Priority::HIGH);
}

TEST_F(TaskServiceTest, getTaskForLabel) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksByLabel("label", false));

  ASSERT_EQ(tasks.size(), 4);
  ASSERT_EQ(tasks[0].getPriority(), Priority::EMPTY);
  ASSERT_EQ(tasks[1].getPriority(), Priority::MEDIUM);
  ASSERT_EQ(tasks[2].getPriority(), Priority::HIGH);
  ASSERT_EQ(tasks[3].getPriority(), Priority::LOW);

  EXPECT_NO_THROW(tasks = service.getTasksByLabel("label", true));
  ASSERT_EQ(tasks.size(), 4);
  ASSERT_EQ(tasks[0].getPriority(), Priority::EMPTY);
  ASSERT_EQ(tasks[1].getPriority(), Priority::LOW);
  ASSERT_EQ(tasks[2].getPriority(), Priority::MEDIUM);
  ASSERT_EQ(tasks[3].getPriority(), Priority::HIGH);
}

TEST_F(TaskServiceTest, getTaskByPriority) {
  std::vector<TaskDTO> tasks;
  EXPECT_NO_THROW(tasks = service.getTasksByPriority(Priority::MEDIUM));

  ASSERT_EQ(tasks.size(), 1);
  ASSERT_EQ(tasks[0].getPriority(), Priority::MEDIUM);
}*/
