//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "API/TaskService.h"


class TaskServiceTest : public ::testing::Test {
 public:
  TaskService service;
  Task task = Task::create("Task", "test", Priority::EMPTY, Date(2020, 10, 10)).value();
  Task subtask = Task::create("Subtask", "test", Priority::EMPTY, Date(2020, 10, 10)).value();
};

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

TEST_F(TaskServiceTest, fullRemove) {
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


TEST_F(TaskServiceTest, postpone) {
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
}









TEST_F(TaskServiceTest, getAllTasks) {
//  EXPECT_NO_THROW(service.getAllTasks());
}

TEST_F(TaskServiceTest, addTask) {
/*  service.addTask(task);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 1);*/
}

TEST_F(TaskServiceTest, addSubtask) {
/*  service.addTask(task);
  service.addSubtask(1, subtask);
  auto tasks = service.getAllTasks();
  ASSERT_EQ(tasks.size(), 2);*/
}

TEST_F(TaskServiceTest, getTasksForToday) {
  //EXPECT_NO_THROW(service.getTasksForToday());
}

TEST_F(TaskServiceTest, getTasksForWeek) {
 // EXPECT_NO_THROW(service.getTasksForWeek());
}

TEST_F(TaskServiceTest, getTaskForLabel) {
/*  service.addTask(task);
  service.addSubtask(1, subtask);
  auto tasks = service.getTasksByLabel("test");
  ASSERT_EQ(tasks.size(), 2);*/
}
