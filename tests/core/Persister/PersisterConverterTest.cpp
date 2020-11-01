//
// Created by Rodion Shyshkin on 25.10.2020.
//

#include <gtest/gtest.h>
#include <task.pb.h>
#include <Persister/PersisterConverter.h>
#include <MemoryModel/ModelAPI/TaskModel.h>

class PersisterConverterTest : public ::testing::Test {
 public:
  void SetUp() override {
    task_with_parent_ = ModelTaskDTO::CreateWithParent(TaskID{2},
                                                       "Task Name With Parent",
                                                       "Task Label",
                                                       Priority::HIGH,
                                                       Date{2020, 12, 31},
                                                       true,
                                                       TaskID{1});
    task_without_parent_ = ModelTaskDTO::CreateWithoutParent(TaskID{3},
                                                             "Task Name Without Parent",
                                                             "Task Label",
                                                             Priority::HIGH,
                                                             Date{2020, 12, 31},
                                                             true);
    root_task_ = ModelTaskDTO::CreateWithoutParent(TaskID{1},
                                                   "Task Parent of Task With Parent",
                                                   "Task Label",
                                                   Priority::LOW,
                                                   Date{2020, 12, 12},
                                                   false);

    incorrect_task_ = ModelTaskDTO::CreateWithoutParent(TaskID{4},
                                                        "",
                                                        "lal",
                                                        Priority::MEDIUM,
                                                        Date{2012, 12, 1},
                                                        true);

    proto_task_with_parent_.mutable_parent_id()->set_id(33);
    proto_task_with_parent_.set_name("name");
    proto_task_with_parent_.set_label("label");
    proto_task_with_parent_.set_priority(ProtoPriority::HIGH);
    proto_task_with_parent_.mutable_deadline()->set_date(2459215);

    proto_task_without_parent_.mutable_parent_id()->set_id(0);
    proto_task_without_parent_.set_name("");
    proto_task_without_parent_.set_label("");
    proto_task_without_parent_.set_priority(ProtoPriority::EMPTY);
    proto_task_without_parent_.mutable_deadline()->set_date(4294967294);

    model_ = std::make_unique<TaskModel>();
    model_->AddTask(root_task_);

    tasks_.push_back(task_with_parent_);
    tasks_.push_back(task_without_parent_);
  }

  void TearDown() override {

  }

 protected:
  ModelTaskDTO task_with_parent_;
  ModelTaskDTO task_without_parent_;
  ModelTaskDTO root_task_;
  ModelTaskDTO incorrect_task_;

  TaskProto proto_task_with_parent_;
  TaskProto proto_task_without_parent_;

  StorageProto storage_proto_;
  StorageProto proto_storage_;
  std::vector<ModelTaskDTO> tasks_;

  std::unique_ptr<TaskModelInterface> model_;
};
/*
TEST_F(PersisterConverterTest, shouldConvertPriorityToProtoCorrectly) {
  ASSERT_EQ(ProtoPriority::EMPTY, persister_converter::PriorityToProto(Priority::EMPTY));
  ASSERT_EQ(ProtoPriority::LOW, persister_converter::PriorityToProto(Priority::LOW));
  ASSERT_EQ(ProtoPriority::MEDIUM, persister_converter::PriorityToProto(Priority::MEDIUM));
  ASSERT_EQ(ProtoPriority::HIGH, persister_converter::PriorityToProto(Priority::HIGH));
}

TEST_F(PersisterConverterTest, shouldConvertProtoToPriorityCorrectly) {
  ASSERT_EQ(Priority::EMPTY, persister_converter::ProtoToPriority(ProtoPriority::EMPTY));
  ASSERT_EQ(Priority::LOW, persister_converter::ProtoToPriority(ProtoPriority::LOW));
  ASSERT_EQ(Priority::MEDIUM, persister_converter::ProtoToPriority(ProtoPriority::MEDIUM));
  ASSERT_EQ(Priority::HIGH, persister_converter::ProtoToPriority(ProtoPriority::HIGH));
}

TEST_F(PersisterConverterTest, shouldConvertSubtaskToProtoCorrectly) {
  TaskProto proto_task;
  ASSERT_NO_THROW(proto_task = persister_converter::TaskToProto(task_with_parent_));
  ASSERT_EQ(proto_task.name(), task_with_parent_.GetName());
  ASSERT_EQ(proto_task.label(), task_with_parent_.GetLabel());
  ASSERT_EQ(proto_task.parent_id().id(), task_with_parent_.GetParentID());
  ASSERT_EQ(proto_task.priority(),
            persister_converter::PriorityToProto(task_with_parent_.GetPriority()));
  ASSERT_EQ(proto_task.deadline().date(), task_with_parent_.GetDueDate().GetDate().day_number());


}

TEST_F(PersisterConverterTest, shouldConvertTaskToProtoCorrectly) {
  TaskProto proto_task;
  ASSERT_NO_THROW(proto_task = persister_converter::TaskToProto(task_without_parent_));
  ASSERT_EQ(proto_task.name(), task_without_parent_.GetName());
  ASSERT_EQ(proto_task.label(), task_without_parent_.GetLabel());
  ASSERT_EQ(proto_task.parent_id().id(), 0);
  ASSERT_EQ(proto_task.priority(),
            persister_converter::PriorityToProto(task_without_parent_.GetPriority()));
  ASSERT_EQ(proto_task.deadline().date(), task_without_parent_.GetDueDate().GetDate().day_number());
}

TEST_F(PersisterConverterTest, shouldConvertProtoToSubtaskCorrectly) {
  ModelTaskDTO dto;
  ASSERT_NO_THROW(dto = persister_converter::ProtoToTask(proto_task_with_parent_));
  ASSERT_EQ(dto.GetName(), proto_task_with_parent_.name());
  ASSERT_EQ(dto.GetLabel(), proto_task_with_parent_.label());
  ASSERT_EQ(dto.GetPriority(),
            persister_converter::ProtoToPriority(proto_task_with_parent_.priority()));
  ASSERT_EQ(dto.GetParentID().GetID(), proto_task_with_parent_.parent_id().id());
  ASSERT_EQ(dto.GetDueDate().GetDate().day_number(), proto_task_with_parent_.deadline().date());
}

TEST_F(PersisterConverterTest, shouldConvertProtoToTaskCorrectly) {
  ModelTaskDTO dto;
  ASSERT_NO_THROW(dto = persister_converter::ProtoToTask(proto_task_without_parent_));
  ASSERT_EQ(dto.GetName(), proto_task_without_parent_.name());
  ASSERT_EQ(dto.GetLabel(), proto_task_without_parent_.label());
  ASSERT_EQ(dto.GetPriority(),
            persister_converter::ProtoToPriority(proto_task_without_parent_.priority()));
  ASSERT_EQ(dto.GetParentID().GetID(), proto_task_without_parent_.parent_id().id());
  ASSERT_EQ(dto.GetDueDate().GetDate().day_number(), proto_task_without_parent_.deadline().date());
  ASSERT_EQ(boost::gregorian::date{boost::gregorian::not_a_date_time},
            boost::gregorian::date{proto_task_without_parent_.deadline().date()});
}
*/
TEST_F(PersisterConverterTest, shouldConvertStorageToProtoCorrectly) {


  ASSERT_NO_THROW(persister_converter::StorageToProto(tasks_, storage_proto_));
  ASSERT_EQ(storage_proto_.tasks_size(), 2);
  ASSERT_EQ(storage_proto_.tasks(0).name(), task_with_parent_.GetName());
  ASSERT_EQ(storage_proto_.tasks(1).name(), task_without_parent_.GetName());
}

TEST_F(PersisterConverterTest, shouldConvertProtoToModelCorrectly) {
  persister_converter::StorageToProto(tasks_, proto_storage_);

  bool result;
  ASSERT_NO_THROW(result = persister_converter::ProtoToModel(proto_storage_, *model_));
  ASSERT_TRUE(result);

  auto tasks = model_->GetAllTasks();
  ASSERT_EQ(tasks.size(), 3);
  ASSERT_EQ(tasks[1].GetName(), task_with_parent_.GetName());
  ASSERT_EQ(tasks[2].GetName(), task_without_parent_.GetName());
}

TEST_F(PersisterConverterTest, shouldNotConvertProtoToModelWithIncorrectTask) {
  tasks_.push_back(incorrect_task_);
  persister_converter::StorageToProto(tasks_, proto_storage_);

  bool result = false;
  ASSERT_NO_THROW(result = persister_converter::ProtoToModel(proto_storage_, *model_));
  ASSERT_FALSE(result);
}