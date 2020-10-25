//
// Created by rodion on 8/4/20.
//
#include <gtest/gtest.h>
#include <MemoryModel/Storage/TaskView.h>

class TaskViewTest : public ::testing::Test {
 public:


  void SetUp() override {
    std::optional<Task> validTask = Task::create("Val.Task", "test", Priority::HIGH,
                                                 Date(2025, 9, 9));
    std::optional<TaskEntity> validEntity = TaskEntity::createTask(validTask.value(), TaskID{1});
    ptrValid = std::make_shared<TaskEntity>(validEntity.value());

    std::optional<Task> invalidTask = Task::create("Inv.Task", "test", Priority::MEDIUM,
                                                   Date(2025, 9, 9));
    std::optional<TaskEntity> invalidEntity = TaskEntity::createTask(invalidTask.value(), TaskID{1});
    ptrInvalid = std::make_shared<TaskEntity>(invalidEntity.value());

    auto today = Date::GetCurrentDate();
    std::optional<Task> todayTask = Task::create("Today Task", "test", Priority::EMPTY,
                                                 today);
    std::optional<TaskEntity> todayEntity = TaskEntity::createTask(todayTask.value(), TaskID{2});
    todayPtr = std::make_shared<TaskEntity>(todayEntity.value());

    auto dayNumber = today.GetDate().day_number() + 7 - today.GetDate().day_of_week();
    boost::gregorian::gregorian_calendar::ymd_type ymdWeek =
        boost::gregorian::gregorian_calendar::from_day_number(dayNumber);
    boost::gregorian::date dateWeek = {ymdWeek.year, ymdWeek.month, ymdWeek.day};
    Date week = Date{dateWeek};
    std::optional<Task> thisWeekTask = Task::create("This week Task", "test", Priority::HIGH,
                                                 week);
    std::optional<TaskEntity> thisWeekEntity = TaskEntity::createTask(thisWeekTask.value(), TaskID{999});
    thisWeek = std::make_shared<TaskEntity>(thisWeekEntity.value());

    auto notWeekDayNumber = today.GetDate().day_number() + 8 - today.GetDate().day_of_week();
    boost::gregorian::gregorian_calendar::ymd_type ymdNotWeek =
        boost::gregorian::gregorian_calendar::from_day_number(notWeekDayNumber);
    boost::gregorian::date dateNotWeek = {ymdNotWeek.year, ymdNotWeek.month, ymdNotWeek.day};
    Date notweek = Date{dateNotWeek};
    std::optional<Task> notThisWeekTask = Task::create("Not this week Task", "test", Priority::LOW,
                                                    notweek);
    std::optional<TaskEntity> notThisWeekEntity = TaskEntity::createTask(notThisWeekTask.value(), TaskID{1001});
    notThisWeek = std::make_shared<TaskEntity>(notThisWeekEntity.value());

    std::optional<Task> task = Task::create("Task", "test", Priority::LOW,
                                                 Date(2095, 4, 12));
    std::optional<TaskEntity> taskEntity = TaskEntity::createTask(task.value(), TaskID{5000});
    ptr = std::make_shared<TaskEntity>(taskEntity.value());
  }

  void TearDown() override {

  }

 protected:
  TaskView task_view_;

  std::shared_ptr<TaskEntity> ptrValid;
  std::shared_ptr<TaskEntity> ptrInvalid;
  std::shared_ptr<TaskEntity> todayPtr;
  std::shared_ptr<TaskEntity> thisWeek;
  std::shared_ptr<TaskEntity> notThisWeek;
  std::shared_ptr<TaskEntity> ptr;
};

TEST_F(TaskViewTest, getAllTasks) {
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(notThisWeek);
  task_view_.AddTask(todayPtr);

  auto tasks = task_view_.GetAllTasks();
  ASSERT_EQ(tasks.size(), 3);
  ASSERT_EQ(tasks[0].GetName(), "Today Task");
  ASSERT_EQ(tasks[1].GetName(), "This week Task");
  ASSERT_EQ(tasks[2].GetName(), "Not this week Task");
}

TEST_F(TaskViewTest, shouldAddValidTask) {
  ASSERT_TRUE(task_view_.AddTask(ptrValid));
}

TEST_F(TaskViewTest, shouldNotAddInvalidTask) {
  ASSERT_TRUE(task_view_.AddTask(ptrValid));
  ASSERT_FALSE(task_view_.AddTask(ptrInvalid));
}

TEST_F(TaskViewTest, shouldRemoveExistingTask) {
  task_view_.AddTask(ptrValid);
  task_view_.AddTask(todayPtr);
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(notThisWeek);

  ASSERT_TRUE(task_view_.RemoveTask(TaskID{2}));

  auto tasks = task_view_.GetAllTasks();
  ASSERT_EQ(tasks.size(), 3);
  ASSERT_EQ(tasks[0].GetName(), "This week Task");
  ASSERT_EQ(tasks[1].GetName(), "Not this week Task");
  ASSERT_EQ(tasks[2].GetName(), "Val.Task");
}

TEST_F(TaskViewTest, shouldNotRemoveUnexistingTask) {
  task_view_.AddTask(ptrValid);
  task_view_.AddTask(todayPtr);
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(notThisWeek);

  task_view_.RemoveTask(TaskID{2});
  ASSERT_FALSE(task_view_.RemoveTask(TaskID{2}));
}

TEST_F(TaskViewTest, getTasksForToday) {
  task_view_.AddTask(todayPtr);
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTodayTasks();
  ASSERT_FALSE(tasks.empty());
  ASSERT_EQ(tasks.size(), 1);
  ASSERT_EQ(tasks[0].GetName(), "Today Task");
}

TEST_F(TaskViewTest, getTasksForWeek) {
  task_view_.AddTask(ptr);
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(notThisWeek);
  task_view_.AddTask(todayPtr);

  auto tasks = task_view_.GetWeekTasks();
  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].GetName(), "Today Task");
  ASSERT_EQ(tasks[1].GetName(), "This week Task");
}

TEST_F(TaskViewTest, getTasksByLabel) {
  task_view_.AddTask(ptr);
  task_view_.AddTask(notThisWeek);
  auto tasks = task_view_.GetTasksByLabel("test");
  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].GetLabel(), "test");
}

TEST_F(TaskViewTest, getTasksByName) {
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(ptr);
  auto tasks = task_view_.GetTasksByName("Task");
  ASSERT_EQ(tasks.size(), 1);
  ASSERT_EQ(tasks[0].GetName(), "Task");
}

TEST_F(TaskViewTest, getTasksByPriority) {
  task_view_.AddTask(thisWeek);
  task_view_.AddTask(ptr);
  task_view_.AddTask(todayPtr);
  auto tasks = task_view_.GetTasksByPriority(Priority::LOW);
  ASSERT_EQ(tasks.size(), 1);
  ASSERT_EQ(tasks[0].GetName(), "Task");
}

