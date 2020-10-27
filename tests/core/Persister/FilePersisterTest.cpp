//
// Created by rodion on 10/6/20.
//

#include <Persister/FilePersister.h>
#include <gtest/gtest.h>
#include <API/TaskService.h>

class FilePersisterTest : public ::testing::Test {
 public:
  void SetUp() override {
/*    auto task = TaskDTO::create(1, "name", "label", Priority::MEDIUM,
                                boost::gregorian::date{2012-10-10}, false);
    auto subtask = TaskDTO::create(2, "subname", "label", Priority::LOW,
                                   boost::gregorian::date{2012-10-10}, false);

    auto subsubtask = TaskDTO::Create(3, "subsubname", "label", Priority::LOW,
                                      boost::gregorian::date{2012-10-10}, false);

    service.add_task_graph(task);
    service.addSubtask(task.getID(), subtask);
    service.add_subtask_graph(subtask.GetID(), subsubtask);*/


    auto task = ModelTaskDTO::CreateWithoutParent(1, "name", "label", Priority::MEDIUM,
                                                  boost::gregorian::date{2012 - 10 - 10}, false);
    auto subtask = ModelTaskDTO::CreateWithParent(2, "subname", "label", Priority::MEDIUM,
                                                  boost::gregorian::date{2012 - 10 - 10}, false, 1);
    auto subsubtask = ModelTaskDTO::CreateWithParent(3, "subsubname", "label", Priority::MEDIUM,
                                                     boost::gregorian::date{2012 - 10 - 10}, false, 2);

    savemodel.AddTask(task);
    savemodel.AddSubtask(task.GetID(), subtask);
    savemodel.AddSubtask(subtask.GetID(), subsubtask);
  }

  void TearDown() override {

  }

 protected:
  TaskModel savemodel;
  TaskModel loadmodel;

};

TEST_F(FilePersisterTest, shouldSave) {
  std::fstream file("test.txt", std::ios::out);
  FilePersister persister{std::move(file), savemodel};

  auto result = persister.Save();
  ASSERT_TRUE(result);
}

TEST_F(FilePersisterTest, shouldNotSaveToIncorrectFile) {
  std::fstream file("test.txt", std::ios::in);
  FilePersister persister{std::move(file), savemodel};

  auto result = persister.Save();
  ASSERT_FALSE(result);
}

TEST_F(FilePersisterTest, shouldLoad) {
  std::fstream file("test.txt", std::ios::in);
  FilePersister persister{std::move(file), loadmodel};

  auto result = persister.Load();
  ASSERT_TRUE(result);

  auto tasks = loadmodel.GetAllTasks();
  ASSERT_EQ(tasks.size(), savemodel.GetAllTasks().size());
}

TEST_F(FilePersisterTest, shouldNotLoadFromIncorrectFile) {
  std::fstream file("unknownFile.txt", std::ios::in);
  FilePersister persister{std::move(file), loadmodel};

  auto result = persister.Load();
  ASSERT_FALSE(result);
}