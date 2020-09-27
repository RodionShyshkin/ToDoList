//
// Created by rodion on 9/27/20.
//

#include <gtest/gtest.h>
#include <MemoryModel/Storage/Serialization/TaskSerializer.h>
#include <MemoryModel/Storage/Serialization/TaskDeserializer.h>

 class SerializationTest : public ::testing::Test {
 public:
  void SetUp() override {
    this->task_ = TaskEntity::createTask(Task::create("name", "label",
                       Priority::MEDIUM, Date{"2020-10-10"}).value(), TaskID{1});

    this->task_proto_.set_name("name");
    this->task_proto_.set_label("label");
    this->task_proto_.set_priority(TaskProto_Priority_MEDIUM);
    this->task_proto_.set_deadline(Date{"2020-10-10"}.GetDate().day_number());
    this->task_proto_.set_completed(false);
    this->task_proto_.set_parent_id(0);
  }

  void TearDown() override {

  }

 protected:
  TaskEntity task_;
  TaskProto task_proto_;
};

TEST_F(SerializationTest, shouldSerializeTask) {
  TaskProto serialized = TaskSerializer::SerializeTaskWithSubtasks(task_);
  ASSERT_EQ(serialized.name(), task_proto_.name());
  ASSERT_EQ(serialized.label(), task_proto_.label());
  ASSERT_EQ(serialized.priority(), task_proto_.priority());
  ASSERT_EQ(serialized.deadline(), task_proto_.deadline());
  ASSERT_EQ(serialized.completed(), task_proto_.completed());
  ASSERT_EQ(serialized.parent_id(), task_proto_.parent_id());
}

TEST_F(SerializationTest, shouldDeserializeTask) {
  std::shared_ptr<TaskEntity> desir = TaskDeserializer::DeserializeTask(task_proto_);
  ASSERT_EQ(desir->GetName(), task_.GetName());
  ASSERT_EQ(desir->GetLabel(), task_.GetLabel());
  ASSERT_EQ(desir->GetPriority(), task_.GetPriority());
  ASSERT_EQ(desir->GetDueTime().GetDate(), task_.GetDueTime().GetDate());
  ASSERT_EQ(desir->GetStatus(), task_.GetStatus());
  ASSERT_EQ(desir->GetSubtasks().size(), task_.GetSubtasks().size());
}