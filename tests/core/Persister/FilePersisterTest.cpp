//
// Created by rodion on 10/6/20.
//

#include <Persister/FilePersister.h>
#include <gtest/gtest.h>
#include <src/core/API/TaskService.h>

class FilePersisterTest : public ::testing::Test {
 public:
  void SetUp() override {
/*    auto task = TaskDTO::create(1, "name", "label", Priority::MEDIUM,
                                boost::gregorian::date{2012-10-10}, false);
    auto subtask = TaskDTO::create(2, "subname", "label", Priority::LOW,
                                   boost::gregorian::date{2012-10-10}, false);

    auto subsubtask = TaskDTO::create(3, "subsubname", "label", Priority::LOW,
                                      boost::gregorian::date{2012-10-10}, false);

    service.addTask(task);
    service.addSubtask(task.getID(), subtask);
    service.addSubtask(subtask.getID(), subsubtask);*/


    auto task = ModelTaskDTO::createWithoutParent(1, "name", "label", Priority::MEDIUM,
                                                  boost::gregorian::date{2012-10-10}, false);
    auto subtask = ModelTaskDTO::createWithParent(2, "subname", "label", Priority::MEDIUM,
                                                  boost::gregorian::date{2012-10-10}, false, 1);
    auto subsubtask = ModelTaskDTO::createWithParent(3, "subsubname", "label", Priority::MEDIUM,
                                                     boost::gregorian::date{2012-10-10}, false, 2);

    savemodel.AddTask(task);
    savemodel.AddSubtask(task.getID(), subtask);
    savemodel.AddSubtask(subtask.getID(), subsubtask);
  }

  void TearDown() override {

  }

 protected:
  TaskModel savemodel;
  TaskModel loadmodel;

};

TEST_F(FilePersisterTest, shouldSave) {
  std::fstream file("test.txt", std::ios::out);
  FilePersister persister{file, savemodel};

  auto result = persister.Save();
  ASSERT_TRUE(result);
}

TEST_F(FilePersisterTest, shouldLoad) {
  std::fstream file("test.txt", std::ios::in);
  FilePersister persister{file, loadmodel};

  auto result = persister.Load();
  ASSERT_TRUE(result);

  auto tasks = loadmodel.getAllTasks();
  ASSERT_EQ(tasks.size(), savemodel.getAllTasks().size());
}