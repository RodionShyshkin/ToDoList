//
// Created by Rodion Shyshkin on 25.10.2020.
//

#include <gtest/gtest.h>
#include <task.pb.h>
#include <Persister/Serialization/ProtoConverter.h>
#include <MemoryModel/ModelAPI/TaskModel.h>

class ProtoConvertersTest : public ::testing::Test {
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

    proto_task_with_parent_.set_parent_id(33);
    proto_task_with_parent_.set_name("name");
    proto_task_with_parent_.set_label("label");
    proto_task_with_parent_.set_priority(TaskProto_Priority_HIGH);
    proto_task_with_parent_.set_deadline(2459215);

    proto_task_without_parent_.set_parent_id(0);
    proto_task_without_parent_.set_name("");
    proto_task_without_parent_.set_label("");
    proto_task_without_parent_.set_priority(TaskProto_Priority_EMPTY);
    proto_task_without_parent_.set_deadline(4294967294);

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

TEST_F(ProtoConvertersTest, shouldConvertPriorityToProtoCorrectly) {
  ASSERT_EQ(TaskProto_Priority_EMPTY, proto_converter::PriorityToProto(Priority::EMPTY));
  ASSERT_EQ(TaskProto_Priority_LOW, proto_converter::PriorityToProto(Priority::LOW));
  ASSERT_EQ(TaskProto_Priority_MEDIUM, proto_converter::PriorityToProto(Priority::MEDIUM));
  ASSERT_EQ(TaskProto_Priority_HIGH, proto_converter::PriorityToProto(Priority::HIGH));
}

TEST_F(ProtoConvertersTest, shouldConvertProtoToPriorityCorrectly) {
  ASSERT_EQ(Priority::EMPTY, proto_converter::ProtoToPriority(TaskProto_Priority_EMPTY));
  ASSERT_EQ(Priority::LOW, proto_converter::ProtoToPriority(TaskProto_Priority_LOW));
  ASSERT_EQ(Priority::MEDIUM, proto_converter::ProtoToPriority(TaskProto_Priority_MEDIUM));
  ASSERT_EQ(Priority::HIGH, proto_converter::ProtoToPriority(TaskProto_Priority_HIGH));
}

TEST_F(ProtoConvertersTest, shouldConvertSubtaskToProtoCorrectly) {
  TaskProto proto_task;
  ASSERT_NO_THROW(proto_task = proto_converter::TaskToProto(task_with_parent_));
  ASSERT_EQ(proto_task.name(), task_with_parent_.GetName());
  ASSERT_EQ(proto_task.label(), task_with_parent_.GetLabel());
  ASSERT_EQ(proto_task.parent_id(), task_with_parent_.GetParentID());
  ASSERT_EQ(proto_task.priority(),
            proto_converter::PriorityToProto(task_with_parent_.GetPriority()));
  ASSERT_EQ(proto_task.deadline(), task_with_parent_.GetDueDate().GetDate().day_number());


}

TEST_F(ProtoConvertersTest, shouldConvertTaskToProtoCorrectly) {
  TaskProto proto_task;
  ASSERT_NO_THROW(proto_task = proto_converter::TaskToProto(task_without_parent_));
  ASSERT_EQ(proto_task.name(), task_without_parent_.GetName());
  ASSERT_EQ(proto_task.label(), task_without_parent_.GetLabel());
  ASSERT_EQ(proto_task.parent_id(), 0);
  ASSERT_EQ(proto_task.priority(),
            proto_converter::PriorityToProto(task_without_parent_.GetPriority()));
  ASSERT_EQ(proto_task.deadline(), task_without_parent_.GetDueDate().GetDate().day_number());
}

TEST_F(ProtoConvertersTest, shouldConvertProtoToSubtaskCorrectly) {
  ModelTaskDTO dto;
  ASSERT_NO_THROW(dto = proto_converter::ProtoToTask(proto_task_with_parent_));
  ASSERT_EQ(dto.GetName(), proto_task_with_parent_.name());
  ASSERT_EQ(dto.GetLabel(), proto_task_with_parent_.label());
  ASSERT_EQ(dto.GetPriority(),
            proto_converter::ProtoToPriority(proto_task_with_parent_.priority()));
  ASSERT_EQ(dto.GetParentID().GetID(), proto_task_with_parent_.parent_id());
  ASSERT_EQ(dto.GetDueDate().GetDate().day_number(), proto_task_with_parent_.deadline());
}

TEST_F(ProtoConvertersTest, shouldConvertProtoToTaskCorrectly) {
  ModelTaskDTO dto;
  ASSERT_NO_THROW(dto = proto_converter::ProtoToTask(proto_task_without_parent_));
  ASSERT_EQ(dto.GetName(), proto_task_without_parent_.name());
  ASSERT_EQ(dto.GetLabel(), proto_task_without_parent_.label());
  ASSERT_EQ(dto.GetPriority(),
            proto_converter::ProtoToPriority(proto_task_without_parent_.priority()));
  ASSERT_EQ(dto.GetParentID().GetID(), proto_task_without_parent_.parent_id());
  ASSERT_EQ(dto.GetDueDate().GetDate().day_number(), proto_task_without_parent_.deadline());
  ASSERT_EQ(boost::gregorian::date{boost::gregorian::not_a_date_time},
            boost::gregorian::date{proto_task_without_parent_.deadline()});
}

TEST_F(ProtoConvertersTest, shouldConvertStorageToProtoCorrectly) {


  ASSERT_NO_THROW(proto_converter::StorageToProto(tasks_, storage_proto_));
  ASSERT_EQ(storage_proto_.tasks_size(), 2);
  ASSERT_EQ(storage_proto_.tasks(0).name(), task_with_parent_.GetName());
  ASSERT_EQ(storage_proto_.tasks(1).name(), task_without_parent_.GetName());
}

TEST_F(ProtoConvertersTest, shouldConvertProtoToModelCorrectly) {
  proto_converter::StorageToProto(tasks_, proto_storage_);

  bool result;
  ASSERT_NO_THROW(result = proto_converter::ProtoToModel(proto_storage_, *model_));
  ASSERT_TRUE(result);

  auto tasks = model_->GetAllTasks();
  ASSERT_EQ(tasks.size(), 3);
  ASSERT_EQ(tasks[1].GetName(), task_with_parent_.GetName());
  ASSERT_EQ(tasks[2].GetName(), task_without_parent_.GetName());
}

TEST_F(ProtoConvertersTest, shouldNotConvertProtoToModelWithIncorrectTask) {
  tasks_.push_back(incorrect_task_);
  proto_converter::StorageToProto(tasks_, proto_storage_);

  bool result = false;
  ASSERT_NO_THROW(result = proto_converter::ProtoToModel(proto_storage_, *model_));
  ASSERT_FALSE(result);
}