//
// Created by rodion on 9/26/20.
//

#include <gtest/gtest.h>
#include <src/core/MemoryModel/CoreAPI/TaskModel.h>

class asdf : public ::testing::Test {

};

TEST_F(asdf, base) {
/*  TaskModel storage;
  auto task = Task::create("name", "label", Priority::HIGH, Date{"2012-10-10"});
  auto subtask = Task::create("subtask", "label", Priority::MEDIUM, Date{"2012-10-10"});
  auto m = TaskEntity::createTask(task.value(), TaskID{1});
  auto mm = TaskEntity::createSubtask(subtask.value(), TaskID{2}, TaskID{1});
  auto k = std::make_shared<TaskEntity>(m);
  auto kk = std::make_shared<TaskEntity>(mm);

  auto mmm = ModelTaskDTO::create(1, "name", "label", Priority::MEDIUM,
                             boost::gregorian::date{2012-10-10}, false);
  auto kkk = ModelTaskDTO::create(2, "subname", "label", Priority::LOW,
                             boost::gregorian::date{2012-10-10}, false);

  auto nnn = ModelTaskDTO::create(3, "subsubname", "label", Priority::LOW,
                             boost::gregorian::date{2012-10-10}, false);

  storage.AddTask(mmm);
  storage.AddSubtask(mmm.getID(), kkk);
  storage.AddSubtask(mmm.getID(), nnn);
  auto status = storage.SaveToDisk("newfile");
  if(status.GetError()) std::cout << "hui";
  status = storage.LoadFromDisk("newfile");*/
}