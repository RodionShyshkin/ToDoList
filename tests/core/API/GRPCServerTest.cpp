//
// Created by Rodion Shyshkin on 31.10.2020.
//

#include <gtest/gtest.h>
#include <task.pb.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <Mocks/MockModel.h>
#include <API/GRPCServer.h>
#include <API/Utils/GRPCConverter.h>

class GRPCServerTest : public ::testing::Test {
 public:
  void SetUp() override {
    task_ = std::make_unique<TaskProto>();
    task_->set_name("name");
    task_->set_label("label");
    task_->set_priority(ProtoPriority::EMPTY);
    auto date = ProtoDate::default_instance().New();
    date->set_date(boost::gregorian::date{2020,
                                          boost::gregorian::Oct, 10}.day_number());
    task_->set_allocated_deadline(date);
    task_->set_completed(true);
    auto id = ProtoTaskID::default_instance().New();
    id->set_id(1);
    task_->set_allocated_parent_id(id);

    subtask_ = std::make_unique<TaskProto>();
    subtask_->set_name("subname");
    subtask_->set_label("");
    subtask_->set_priority(ProtoPriority::EMPTY);
    auto subdate = ProtoDate::default_instance().New();
    subdate->set_date(boost::gregorian::date{
      boost::gregorian::not_a_date_time}.day_number());
    subtask_->set_allocated_deadline(subdate);
    subtask_->set_completed(false);
    auto subid = ProtoTaskID::default_instance().New();
    subid->set_id(1);
    subtask_->set_allocated_parent_id(subid);

    id_ = std::make_unique<ProtoTaskID>();
    id_->set_id(1);

    dto_task_ = ModelTaskDTO::CreateWithoutParent(
          1,
          task_->name(),
          task_->label(),
          proto_converter::ProtoToPriority(task_->priority()),
          Date{boost::gregorian::date{task_->deadline().date()}},
          task_->completed()
        );
    dto_subtask_ = ModelTaskDTO::CreateWithParent(
          2,
          subtask_->name(),
          subtask_->label(),
          proto_converter::ProtoToPriority(subtask_->priority()),
          Date{boost::gregorian::date{subtask_->deadline().date()}},
          subtask_->completed(),
          subtask_->parent_id().id()
    );
  }

  void TearDown() override {

  }

 protected:
  std::unique_ptr<TaskProto> task_;
  std::unique_ptr<TaskProto> subtask_;

  ModelTaskDTO dto_task_;
  ModelTaskDTO dto_subtask_;

  std::unique_ptr<ProtoTaskID> id_;
};

TEST_F(GRPCServerTest, shouldNotAddEmptyTask) {
  auto model = std::make_unique<MockModel>();

  auto request = AddTaskRequest::default_instance().New();
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  grpc::Status result;
  EXPECT_NO_THROW(result = server.AddTask(nullptr, request, response));
  ASSERT_FALSE(result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::INVALID_TASK);
}

TEST_F(GRPCServerTest, shouldAddCorrectTask) {
  auto model = std::make_unique<MockModel>();
  EXPECT_CALL(*model, AddTask).Times(1)
        .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto request = AddTaskRequest::default_instance().New();
  request->set_allocated_task(task_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  auto model_result = server.AddTask(nullptr, request, response);
  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::NO_ERRORS);
}

TEST_F(GRPCServerTest, shouldNotAddInvalidTask) {
  auto model = std::make_unique<MockModel>();
  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(
          OperationResult<StorageError>::Fail(StorageError::INVALID_TASK)));

  auto request = AddTaskRequest::default_instance().New();
  request->set_allocated_task(task_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  auto model_result = server.AddTask(nullptr, request, response);
  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::INVALID_TASK);
}

TEST_F(GRPCServerTest, shouldNotAddTaskWithWrongID) {
  auto model = std::make_unique<MockModel>();
  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(
          OperationResult<StorageError>::Fail(StorageError::WRONG_TASK_ID)));

  auto request = AddTaskRequest::default_instance().New();
  request->set_allocated_task(task_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  auto model_result = server.AddTask(nullptr, request, response);
  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::WRONG_TASK_ID);
}

TEST_F(GRPCServerTest, shouldNotAddSubtaskWithoutID) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto request = AddSubtaskRequest::default_instance().New();
  request->set_allocated_task(subtask_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  auto k = server.AddTask(nullptr, add_request, response);
  auto model_result = server.AddSubtask(nullptr, request, response);
  ASSERT_FALSE(model_result.ok());
}

TEST_F(GRPCServerTest, shouldAddCorrectSubtask) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, AddSubtask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto request = AddSubtaskRequest::default_instance().New();
  request->set_allocated_task(subtask_.get());
  request->set_allocated_parent(id_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, response);
  auto model_result = server.AddSubtask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::NO_ERRORS);
}


TEST_F(GRPCServerTest, shouldNotRemoveTaskWithModelError) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, RemoveTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Fail(
          StorageError::TASK_NOT_FOUND)));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto request = RemoveTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, response);
  auto model_result = server.RemoveTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::TASK_NOT_FOUND);
}

TEST_F(GRPCServerTest, shouldNotRemoveUnexistingTask) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto request = RemoveTaskRequest::default_instance().New();
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, response);
  auto model_result = server.RemoveTask(nullptr, request, response);

  ASSERT_FALSE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::TASK_NOT_FOUND);
}

TEST_F(GRPCServerTest, shouldRemoveTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, RemoveTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto request = RemoveTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = StorageResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, response);
  auto model_result = server.RemoveTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoStorageError::NO_ERRORS);
}

TEST_F(GRPCServerTest, shouldNotCompleteTaskWithModelError) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, CompleteTask).Times(1)
      .WillOnce(::testing::Return(false));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = CompleteTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.CompleteTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->status(), false);
}

TEST_F(GRPCServerTest, shouldNotCompleteUnexistingTask) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = CompleteTaskRequest::default_instance().New();
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.CompleteTask(nullptr, request, response);

  ASSERT_FALSE(model_result.ok());
  ASSERT_EQ(response->status(), false);
}

TEST_F(GRPCServerTest, shouldCompleteTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, CompleteTask).Times(1)
      .WillOnce(::testing::Return(true));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = CompleteTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.CompleteTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->status(), true);
}

TEST_F(GRPCServerTest, shouldNotPostponeTaskWithModelError) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, PostponeTask).Times(1)
      .WillOnce(::testing::Return(false));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = PostponeTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto date = ProtoDate::default_instance().New();
  date->set_date(boost::gregorian::date{2020,
                                        boost::gregorian::Jan, 30}.day_number());
  request->set_allocated_date(date);
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.PostponeTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->status(), false);
}

TEST_F(GRPCServerTest, shouldNotPostponeTaskWithoutDate) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = PostponeTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.PostponeTask(nullptr, request, response);

  ASSERT_FALSE(model_result.ok());
  ASSERT_EQ(response->status(), false);
}

TEST_F(GRPCServerTest, shouldPostponeTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, PostponeTask).Times(1)
      .WillOnce(::testing::Return(true));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = PostponeTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto date = ProtoDate::default_instance().New();
  date->set_date(boost::gregorian::date{2020,
                                        boost::gregorian::Jan, 30}.day_number());
  request->set_allocated_date(date);
  auto response = BoolResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.PostponeTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->status(), true);
}

TEST_F(GRPCServerTest, shouldNotGetTaskWithModelError) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTask).Times(1)
      .WillOnce(::testing::Return(std::nullopt));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = GetTaskResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_NE(response->task().name(), task_->name());
}

TEST_F(GRPCServerTest, shouldGetTaskCorrectly) {
  auto model = std::make_unique<MockModel>();

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTask).Times(1)
      .WillOnce(::testing::Return(dto_task_));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTaskRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = GetTaskResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTask(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->task().name(), task_->name());
}

TEST_F(GRPCServerTest, shouldGetAllTasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetAllTasks).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetAllTasksRequest::default_instance().New();
  request->set_is_sorted_by_priority(true);
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetAllTasks(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetTodayTasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTasksForToday).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTodayTasksRequest::default_instance().New();
  request->set_is_sorted_by_priority(true);
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTodayTasks(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetWeekTasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTasksForWeek).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetWeekTasksRequest::default_instance().New();
  request->set_is_sorted_by_priority(true);
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetWeekTasks(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetTasksByLabelCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTasksByLabel).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTasksByLabelRequest::default_instance().New();
  request->set_is_sorted_by_priority(true);
  request->set_label("label");
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTasksByLabel(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetTasksByNameCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTasksByName).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTasksByNameRequest::default_instance().New();
  request->set_is_sorted_by_priority(true);
  request->set_name("name");
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTasksByName(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetTasksByPriorityCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetTasksByPriority).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetTasksByPriorityRequest::default_instance().New();
  request->set_priority(ProtoPriority::LOW);
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetTasksByPriority(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldGetSubtasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetSubtasks).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = GetSubtasksRequest::default_instance().New();
  request->set_allocated_id(id_.get());
  auto response = TasksListResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.GetSubtasks(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->tasks_size(), 2);
}

TEST_F(GRPCServerTest, shouldSaveTasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));
  EXPECT_CALL(*model, GetAllTasks).Times(1)
      .WillOnce(::testing::Return(result_vector));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = SaveTasksRequest::default_instance().New();
  request->set_filepath("huinya.txt");
  auto response = PersistResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.Save(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoPersistError::NONE);
}

TEST_F(GRPCServerTest, shouldLoadTasksCorrectly) {
  auto model = std::make_unique<MockModel>();

  std::vector<ModelTaskDTO> result_vector;
  result_vector.push_back(dto_task_);
  result_vector.push_back(dto_subtask_);

  EXPECT_CALL(*model, AddTask).Times(1)
      .WillOnce(::testing::Return(OperationResult<StorageError>::Success()));

  auto add_request = AddTaskRequest::default_instance().New();
  add_request->set_allocated_task(task_.get());
  auto add_response = StorageResponse::default_instance().New();

  auto request = LoadTasksRequest::default_instance().New();
  request->set_filepath("huinya.txt");
  auto response = PersistResponse::default_instance().New();

  auto server = GRPCServer{std::move(model)};

  server.AddTask(nullptr, add_request, add_response);
  auto model_result = server.Load(nullptr, request, response);

  ASSERT_TRUE(model_result.ok());
  ASSERT_EQ(response->error(), ProtoPersistError::NONE);
}