//
// Created by rodion on 10/6/20.
//

#include <Persister/FilePersister.h>
#include <gtest/gtest.h>
#include <src/core/API/TaskService.h>

class FilePersisterTest : public ::testing::Test {
 public:
  void SetUp() override {
    auto task = TaskDTO::create(1, "name", "label", Priority::MEDIUM,
                                boost::gregorian::date{2012-10-10}, false);
    auto subtask = TaskDTO::create(2, "subname", "label", Priority::LOW,
                                   boost::gregorian::date{2012-10-10}, false);

    auto subsubtask = TaskDTO::create(3, "subsubname", "label", Priority::LOW,
                                      boost::gregorian::date{2012-10-10}, false);

    service.addTask(task);
    service.addSubtask(task.getID(), subtask);
    service.addSubtask(subtask.getID(), subsubtask);
  }

  void TearDown() override {

  }

 protected:
  TaskService service;
};

TEST_F(FilePersisterTest, shouldSaveToFile) {
  auto status = service.Save("testfile.txt");
  ASSERT_EQ(status.GetError(), std::nullopt);
}

TEST_F(FilePersisterTest, shouldLoadFromFile) {
  auto status = service.Load("testfile.txt");
  ASSERT_EQ(status.GetError(), std::nullopt);

  auto tasks = service.getAllTasks(false);
  ASSERT_EQ(tasks.size(), 3);
}
